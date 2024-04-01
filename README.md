# Online Store Management System

This project is an online store management system implemented in C. It provides essential functionalities for managing an online store, including user authentication, product management, and cart handling.

## Features

- **User Management**: Users can register with unique usernames and passwords.
- **Login System**: Users can log in with their registered credentials.
- **User and Admin Access**: Separate menus for users and administrators.
- **User Menu**:
  - Display items available in the store.
  - Add products to the cart.
  - View cart.
  - Checkout items in the cart.
  - Submit feedback.
- **Admin Menu**:
  - Add new products to the inventory.
  - Delete existing products from the inventory.
  - Track products by their ID.
  - Display all products in the inventory.
  - Display feedback submitted by users.
- **Product Management**: Products are stored in a CSV file, including their ID, name, price, and quantity.
- **Cart Management**: Users can add products to their cart, view the cart, and checkout items.
- **Feedback System**: Users can submit feedback, which is stored in a file.
- **Input Validation**: Validates user inputs to prevent errors.

## Usage

1. Clone the repository:

```bash
git clone https://github.com/your-username/online-store-management-system.git

gcc main.c -o online_store

./online_store

Security Considerations

Password Security: Storing passwords in plain text files is not secure. Consider hashing passwords before storage for better security.

Data Privacy: Ensure sensitive user data is handled securely and adheres to privacy regulations.

Contributing
Contributions are welcome! If you'd like to contribute to this project, please fork the repository, make your changes, and submit a pull request
