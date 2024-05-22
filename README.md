### ProjectAdmin_D7

# ProjectAdmin Module for Drupal 7

Welcome to the **ProjectAdmin** module for Drupal 7! This module is designed to provide comprehensive project management capabilities within your Drupal 7 site. It includes features for creating and managing project-related content, ensuring seamless integration and ease of use.

## Features

- **Content Types**: Automatically creates two interconnected content types upon installation.
- **Custom Logic**: Utilizes separate `.inc` or `.php` files for each content type to handle custom logic.
- **CRUD Operations**: Supports full CRUD (Create, Read, Update, Delete) operations for the content types.
- **Views Integration**: Includes custom views for displaying content and importing Views upon installation.
- **Export Reports**: Allows exporting reports from one of the views.

## Installation

To install the **ProjectAdmin** module, follow these steps:

1. **Download and Enable the Module**:
    ```bash
    drush dl projectadmin_d7
    drush en projectadmin_d7 -y
    ```

2. **Run Database Updates**:
    ```bash
    drush updb -y
    ```

3. **Clear Caches**:
    ```bash
    drush cc all
    ```

## Uninstallation

To uninstall the module and clean up all related content:

1. **Disable the Module**:
    ```bash
    drush dis projectadmin_d7 -y
    ```

2. **Uninstall the Module**:
    ```bash
    drush pm-uninstall projectadmin_d7 -y
    ```

## Content Types

The **ProjectAdmin** module creates the following content types:

1. **Project**:
    - Fields: File, Date, Email, Select, Node Reference, Number
2. **Task**:
    - Related to the **Project** content type via a node reference field.

## Views

The module provides the following views:

1. **Project Overview**: 
    - Custom view for displaying important project information in a table or list format.
    - Accessible only by a specific user role.
  
2. **Task List**:
    - Imported from the Views module upon installation.
    - Provides a comprehensive list of tasks related to projects.

## Exporting Reports

Users can export reports from the **Task List** view to analyze project data effectively.

## Usage

1. **Create Projects and Tasks**:
    - Navigate to **Content > Add content > Project** or **Task** to create new entries.

2. **Manage Content**:
    - Use the provided CRUD operations to manage your projects and tasks.

3. **View Projects and Tasks**:
    - Access the **Project Overview** and **Task List** views from the navigation menu to see your project data.

## Customization

Feel free to customize the module as per your requirements. The logic for each content type is separated into `.inc` or `.php` files, making it easier to extend functionality.

## Contributions

Contributions are welcome! Please submit pull requests or open issues on the [GitHub repository](https://github.com/yourusername/projectadmin_d7).

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

---

Thank you for using **ProjectAdmin**! We hope this module enhances your project management experience in Drupal 7. For any questions or support, please open an issue on our GitHub repository.

Happy managing!
