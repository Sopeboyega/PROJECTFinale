#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure for user information
typedef struct {
    char username[50];
    char password[50];
} User;

// Structure for admin information
typedef struct {
    char username[50];
    char password[50];
} Admin;

// Function prototypes for user management
void signUpUser();
void signUpAdmin();
void loginUser();
void loginAdmin();
void showUserMenu();
void showAdminMenu();
void addToCart(const char *name, int quantity);
void display_items(const char *file_name);
void view_cart();
void checkout();
void exit_program();
void populate_products(const char *file_name);
void addProduct();
void deleteProduct();
void trackProduct();
void displayProducts();
void clear_cart();
void update_inventory(const char *file_name);
int findProductIndex(const char *product_id);

#define MAX_COLUMNS 10
#define MAX_LENGTH 100
#define MAX_PRODUCTS 100

typedef struct {
    char product_id[MAX_LENGTH];
    char name[MAX_LENGTH];
    double price;
    int quantity;
} Product;

char currentUserType[10]; 
int numProducts = 0;

typedef struct {
    char product_id[MAX_LENGTH];
    char name[MAX_LENGTH];
    double price;
    int quantity;
} CartItem;

CartItem cart[MAX_PRODUCTS];
int cart_size = 0;
Product products[MAX_PRODUCTS];

int main() {
       

    
    const char *file_name = "inventory.csv";
    int choice;

 populate_products("inventory.csv");

    printf("Welcome to the online store!\n");

    // Show user and admin signup options
    printf("Do you want to sign up as a user or admin?\n");
    printf("1. User\n");
    printf("2. Admin\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            signUpUser();
            break;
        case 2:
            signUpAdmin();
            break;
        default:
            printf("Invalid choice. Exiting program.\n");
            exit(EXIT_FAILURE);
    }

   // After signup, proceed to login
printf("Account created successfully!\n");
printf("Do you want to login as a user or admin?\n");
printf("1. User\n");
printf("2. Admin\n");
printf("Enter your choice: ");
int loginChoice;
scanf("%d", &loginChoice);

if (loginChoice == 1) {
    loginUser();
} else if (loginChoice == 2) {
    loginAdmin();
} else {
    printf("Invalid choice. Exiting program.\n");
    exit(EXIT_FAILURE);
}


    // Load product data
    populate_products(file_name);

    // Display Main Menu based on user type
    if (strcmp(currentUserType, "user") == 0) {
        showUserMenu();
    } else if (strcmp(currentUserType, "admin") == 0) {
           showAdminMenu(); // Call the admin menu function;
    } else {
        printf("Unknown user type. Exiting program.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

// Function to allow user signup
void signUpUser() {
    User newUser;

    printf("Enter your desired username: ");
    scanf("%s", newUser.username);
    printf("Enter your desired password: ");
    scanf("%s", newUser.password);

    // Save user info to file or database
    FILE *userFile = fopen("users.txt", "a");
    if (userFile == NULL) {
        printf("Error opening user file.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(userFile, "%s %s\n", newUser.username, newUser.password);
    fclose(userFile);

    printf("User signup successful!\n");
}

// Function to allow admin signup
void signUpAdmin() {
    Admin newAdmin;

    printf("Enter your desired admin username: ");
    scanf("%s", newAdmin.username);
    printf("Enter your desired admin password: ");
    scanf("%s", newAdmin.password);

    // Save admin info to file or database
    FILE *adminFile = fopen("admins.txt", "a");
    if (adminFile == NULL) {
        printf("Error opening admin file.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(adminFile, "%s %s\n", newAdmin.username, newAdmin.password);
    fclose(adminFile);

    printf("Admin signup successful!\n");
}

// Function to handle user login
void loginUser() {
    User users[100];
    char username[50];
    char password[50];

    // Load user info from file or database
    FILE *userFile = fopen("users.txt", "r");
    if (userFile == NULL) {
        printf("Error opening user file.\n");
        exit(EXIT_FAILURE);
    }
    int numUsers = 0;
    while (fscanf(userFile, "%s %s", users[numUsers].username, users[numUsers].password) == 2) {
        numUsers++;
    }
    fclose(userFile);

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    int authenticated = 0;
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            authenticated = 1;
            break;
        }
    }

    if (authenticated) {
        printf("User login successful.\n");
        strcpy(currentUserType, "user");
    } else {
        printf("Invalid username or password. Exiting program.\n");
        exit(EXIT_FAILURE);
    }
}

// Function to handle admin login
void loginAdmin() {
    Admin admins[100];
    char username[50];
    char password[50];

    // Load admin info from file or database
    FILE *adminFile = fopen("admins.txt", "r");
    if (adminFile == NULL) {
        printf("Error opening admin file.\n");
        exit(EXIT_FAILURE);
    }
    int numAdmins = 0;
    while (fscanf(adminFile, "%s %s", admins[numAdmins].username, admins[numAdmins].password) == 2) {
        numAdmins++;
    }
    fclose(adminFile);

    printf("Enter your admin username: ");
    scanf("%s", username);
    printf("Enter your admin password: ");
    scanf("%s", password);

    int authenticated = 0;
    for (int i = 0; i < numAdmins; i++) {
        if (strcmp(admins[i].username, username) == 0 && strcmp(admins[i].password, password) == 0) {
            authenticated = 1;
            break;
        }
    }

    if (authenticated) {
        printf("Admin login successful.\n");
        strcpy(currentUserType, "admin");
    } else {
        printf("Invalid admin username or password. Exiting program.\n");
        exit(EXIT_FAILURE);
    }
}

// Function to display user menu
// Function to display user menu
void showUserMenu() {
    const char *file_name = "inventory.csv";  // name of CSVFILE
    int choice;
    int quantity;

    // Load product data
    populate_products(file_name);

    // Display Main Menu
    do {
        printf("\nMenu:\n");
        printf("1. Display Items\n");
        printf("2. Add Product to Cart\n");
        printf("3. View Cart\n");
        printf("4. Checkout\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayProducts() ;
                break;
            case 2: {
                char name[MAX_LENGTH];
                printf("Enter the product name: ");
                scanf("%s", name);
                printf("Enter the quantity: ");
                scanf("%d", &quantity);
                addToCart(name, quantity);
                break;
            }
            case 3:
                view_cart();
                break;
            case 4:
                checkout(file_name);
                break;
            case 5:
                exit_program();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}

// Function to display admin menu
void showAdminMenu() {
    const char *file_name = "inventory.csv"; // name of CSV file

    // Load product data
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error: Unable to open file '%s'\n", file_name);
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%s %s %lf %d", products[numProducts].product_id, products[numProducts].name, &products[numProducts].price, &products[numProducts].quantity) == 4) {
        numProducts++;
    }

    fclose(file);

    int choice;
    do {
        printf("\nAdmin Menu:\n");
        printf("1. Add Product\n");
        printf("2. Delete Product\n");
        printf("3. Track Product\n");
        printf("4. Display Products\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                deleteProduct();
                break;
            case 3:
                trackProduct();
                break;
            case 4:
                displayProducts();
                break;
            case 5:
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}

int findProductIndex(const char *product_id) {
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(products[i].product_id, product_id) == 0) {
            return i;  // Found the product, return its index
        }
    }
    return -1;  // Product not found
}

// Trim leading and trailing whitespace from a string
void trim(char *str) {
    char *end;

    // Trim leading whitespace
    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == 0) {  // All whitespace
        return;
    }

    // Trim trailing whitespace
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    // Null-terminate the trimmed string
    *(end + 1) = '\0';
}



// Function to read data from CSV and populate products array
void populate_products(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error: Unable to open file '%s'\n", file_name);
        exit(EXIT_FAILURE);
    }

    char line[MAX_COLUMNS * MAX_LENGTH];  // Allocate space for entire line
    int line_count = 0; // A variable to count the number of lines read.

    while (fgets(line, sizeof(line), file)) {
        if (line_count == 0) { // Skip header line
            line_count++;
            continue;
        }

        if (numProducts >= MAX_PRODUCTS) {
            printf("Error: Maximum capacity reached. Cannot add more products.\n");
            break;
        }

        char *token = strtok(line, ","); // strtok is used for tokenizing the string.
        int column_count = 0; // Keeps track of the number of columns processed.
        Product product;

        while (token != NULL && column_count < MAX_COLUMNS) {
            switch (column_count) {
                case 0:
                    strcpy(product.product_id, token);
                    break;
                case 1:
                    strcpy(product.name, token);
                    break;
                case 2:
                    product.price = atof(token);
                    break;
                case 3:
                    product.quantity = atoi(token);
                    break;
                default:
                    break;
            }
            token = strtok(NULL, ",");
            column_count++;
        }

        // Check if the product already exists in the array
        int existing_index = findProductIndex(product.product_id);
        if (existing_index != -1) {
            // Product already exists, update its information
            products[existing_index] = product;
        } else {
            // Product doesn't exist, add it to the products array
            trim(product.name);
            products[numProducts] = product;
            numProducts++;
        }

        line_count++;
    }

    fclose(file);
}


void strToLower(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}



// Function to add a product to the cart
void addToCart(const char *name, int quantity) {
    int found = 0;
    for (int i = 0; i < numProducts; i++) {
        // Preprocess product name: remove leading/trailing whitespace and convert to lowercase
        char processedName[MAX_LENGTH];
        strcpy(processedName, products[i].name);
        trim(processedName);
        strToLower(processedName);

        // Preprocess the provided name in the same way
        char providedName[MAX_LENGTH];
        strcpy(providedName, name);
        trim(providedName);
        strToLower(providedName);



        // Compare the processed names
        if (strcmp(processedName,providedName) == 0) {
            // Check if enough quantity is available
            if (products[i].quantity >= quantity) {
                // Add product to cart
                strcpy(cart[cart_size].product_id, products[i].product_id);
                strcpy(cart[cart_size].name, products[i].name);
                cart[cart_size].price = products[i].price;
                cart[cart_size].quantity = quantity;
                cart_size++;

                // Update available quantity in the products array
                products[i].quantity -= quantity;
                printf("Added %d of %s to the cart.\n", quantity, name);
                found = 1;
            } else {
                printf("Insufficient quantity available for %s.\n", name);
            }
            break;
        }
    }

    if (!found) {
        printf("Product with name '%s' not found.\n", name);
    }
}





// Function to view cart contents
void view_cart() {
    if (cart_size == 0) {
        printf("Cart is empty.\n");
        return;
    }

    printf("Cart Contents:\n");
    double total_price = 0.0;
    for (int i = 0; i < cart_size; i++) {
        double subtotal = cart[i].quantity * cart[i].price;
        printf("Product ID: %s, Name: %s, Quantity: %d, Price per item: $%.2f, Subtotal: $%.2f\n",
               cart[i].product_id, cart[i].name, cart[i].quantity, cart[i].price, subtotal);
        total_price += subtotal;
    }
    printf("Total Price: $%.2f\n", total_price);
}


// Function to checkout and finalize the order
// Function to checkout and finalize the order
void checkout(const char *file_name) {
    printf("\nCheckout\n");
    printf("Confirm your order (yes/no): ");
    char confirmation[10];
    scanf("%s", confirmation);

    if (strcasecmp(confirmation, "yes") == 0) {
        double total_price = 0.0;

        // Calculate the total price based on items in the cart
        for (int i = 0; i < cart_size; i++) {
            total_price += cart[i].quantity * cart[i].price;
        }

        // Display items in the cart and subtotal
        printf("Cart Contents:\n");
        for (int i = 0; i < cart_size; i++) {
            double subtotal = cart[i].quantity * cart[i].price;
            printf("Product ID: %s, Name: %s, Quantity: %d, Price per item: $%.2f, Subtotal: $%.2f\n",
                   cart[i].product_id, cart[i].name, cart[i].quantity, cart[i].price, subtotal);
        }
        printf("Total Price: $%.2f\n", total_price);

        // Update the inventory
        update_inventory(file_name);

        // Clear the cart
        clear_cart();

        printf("Order finalized. Thank you for your purchase!\n");
    } else {
        printf("Order canceled. Products remain in the cart.\n");
    }
}



// Function to exit the program
void exit_program() {
    printf("Exiting program.\n");
    exit(EXIT_SUCCESS);
}


// Function to add a product
void addProduct() {
    if (numProducts >= MAX_PRODUCTS) {
        printf("Error: Maximum number of products reached.\n");
        return;
    }

    printf("Enter product details:\n");
    char product_id[MAX_LENGTH];
    char name[MAX_LENGTH];
    double price;
    int quantity;

    printf("Product ID: ");
    scanf("%s", product_id);
    printf("Name: ");
    scanf("%s", name);
    printf("Price: ");
    scanf("%lf", &price);
    printf("Quantity: ");
    scanf("%d", &quantity);

    // Open the inventory.csv file in append mode
    FILE *file = fopen("inventory.csv", "a");
    if (file == NULL) {
        printf("Error: Unable to open file 'inventory.csv'\n");
        return;
    }

    // Append the new product information to the file
    fprintf(file, "%s,%s,%.2lf,%d\n", product_id, name, price, quantity);
    fclose(file);

    printf("Product added successfully.\n");
}


void deleteProduct() {
    char product_id[MAX_LENGTH];
    printf("Enter product ID to delete: ");
    scanf("%s", product_id);

    int found = 0;
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(products[i].product_id, product_id) == 0) {
            // Remove product by shifting remaining products
            for (int j = i; j < numProducts - 1; j++) {
                products[j] = products[j + 1];
            }
            numProducts--;
            found = 1;
            printf("Product deleted successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Product with ID '%s' not found.\n", product_id);
    }
}

// Function to track a product
void trackProduct() {
    char product_id[MAX_LENGTH];
    printf("Enter product ID to track: ");
    scanf("%s", product_id);

    int found = 0;
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(products[i].product_id, product_id) == 0) {
            printf("Product found:\n");
            printf("Product ID: %s\n", products[i].product_id);
            printf("Name: %s\n", products[i].name);
            printf("Price: %.2lf\n", products[i].price);
            printf("Quantity: %d\n", products[i].quantity);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product with ID '%s' not found.\n", product_id);
    }
}



// Function to display all products
void displayProducts() {
    if (numProducts == 0) {
        printf("No products in inventory.\n");
        return;
    }

    printf("Products in inventory:\n");
    for (int i = 0; i < numProducts; i++) {
        printf("Product ID: %s, Name: %s, Price: %.2lf, Quantity: %d\n",
               products[i].product_id, products[i].name, products[i].price, products[i].quantity);
    }
}



//convert string to lower  case


void update_inventory(const char *file_name) {
    // Open the inventory file in write mode to clear its contents
    FILE *file = fopen("inventory.csv", "w");
    if (file == NULL) {
        printf("Error: Unable to open inventory file.\n");
        return;
    }
    fclose(file);

    // Reopen the inventory file in append mode to write the updated products
    file = fopen("inventory.csv", "a");
    if (file == NULL) {
        printf("Error: Unable to open inventory file.\n");
        return;
    }

    // Write the products from the populated struct to the inventory file
    for (int i = 0; i < numProducts; i++) {
        fprintf(file, "%s,%s,%.2lf,%d\n", products[i].product_id, products[i].name, products[i].price, products[i].quantity);
    }

    fclose(file);
}

void clear_cart() {
    // Clear the cart by resetting its size to 0
    cart_size = 0;
}

void submitFeedback() {
    char feedback[MAX_LENGTH];

    // Prompt the user for feedback
    printf("Please enter your feedback (max %d characters): ", MAX_LENGTH);
    getchar(); // Clear input buffer
    fgets(feedback, MAX_LENGTH, stdin);

    // Open the feedback file in append mode
    FILE *file = fopen("feedback.txt", "a");
    if (file == NULL) {
        printf("Error opening feedback file.\n");
        return;
    }

    // Write the feedback to the file
    fprintf(file, "%s\n", feedback);

    fclose(file);

    printf("Thank you for your feedback!\n");
}



