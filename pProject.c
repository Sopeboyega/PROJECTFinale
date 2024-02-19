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
void submitFeedback();
void registerUser();
void login();
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

    populate_products(file_name);
system("cls");
    printf("Welcome to the online store!\n");
 
 do {
    system("cls");
        printf("Main Menu:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                login();
                break;
            case 3:
                exit_program();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1); // Loop indefinitely until user chooses to exit


    return 0;
}


// Function to allow user signup
void registerUser() {
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

    printf("User registered successfully!\n");
}


// Function to login
void login() {
    char username[50];
    char password[50];

    do {
        printf("Enter your username: ");
        scanf("%s", username);
        printf("Enter your password: ");
        scanf("%s", password);

        // Check if the credentials match any user
        FILE *userFile = fopen("users.txt", "r");
        if (userFile == NULL) {
            printf("Error opening user file.\n");
            exit(EXIT_FAILURE);
        }

        char storedUsername[50];
        char storedPassword[50];
        int authenticated = 0;

        while (fscanf(userFile, "%s %s", storedUsername, storedPassword) == 2) {
            if (strcmp(storedUsername, username) == 0 && strcmp(storedPassword, password) == 0) {
                authenticated = 1;
                break;
            }
        }
        fclose(userFile);

        if (authenticated) {
            printf("Login successful.\n");
            strcpy(currentUserType, "user");
            break;
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    } while (1);

    // Redirect to user or admin menu based on credentials
    if (strcmp(username, "admin4787") == 0 && strcmp(password, "adminstrator") == 0) {
        strcpy(currentUserType, "admin");
        showAdminMenu();
    } else {
        showUserMenu();
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
     system("cls");
    do {
        printf("\nMenu:\n");
        printf("1. Display Items\n");
        printf("2. Add Product to Cart\n");
        printf("3. View Cart\n");
        printf("4. Checkout\n");
        printf("5. Sumbit Feedback\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            system("cls");
                displayProducts() ;
                break;
            case 2: {
                system("cls");
                char name[MAX_LENGTH];
                printf("Enter the product name: ");
                scanf("%s", name);
                printf("Enter the quantity: ");
                scanf("%d", &quantity);
                addToCart(name, quantity);
                break;
            }
            case 3:
            system("cls");
                view_cart();
                break;
            case 4:
            system("cls");
                checkout(file_name);
                break;
            case 5:
            system("cls");
                submitFeedback();
                break;
            case 6:
            system("cls");
                exit_program();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
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




