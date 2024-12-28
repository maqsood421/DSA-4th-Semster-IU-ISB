#include <iostream>
using namespace std;

class Product {
public:
    int unique_id;
    int price;

    Product() {
        unique_id = -1;
        price = 0;
    }
};

class Inventory {
public:
    Product products[100]; // maximum 100 products
    int productCnt;

    Inventory() : productCnt(0) {} // initialize productCnt to zero

    // adds product in inventory
    void addProduct(int id, int price) {
        if (hasUniqueId(id)) {
            products[productCnt].unique_id = id;
            products[productCnt].price = price;
            productCnt++;
            cout << "Product added successfully!\n";
        } else {
            cout << "ID is already present!\n";
        }
    }

    // checks if id is unique or not
    bool hasUniqueId(int id) {
        for (int i = 0; i < productCnt; i++) {
            if (products[i].unique_id == id) {
                return false;
            }
        }
        return true;
    }

    // removes a product by its ID
    void removeProduct(int id) {
        int index = -1;
        for (int i = 0; i < productCnt; i++) {
            if (products[i].unique_id == id) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Product not found!\n";
            return;
        }

        for (int i = index; i < productCnt - 1; i++) {
            products[i] = products[i + 1];
        }
        productCnt--;
        cout << "Product removed successfully!\n";
    }

    // sorts products by unique_id using selection sort
    void sortProductsById() {
        for (int i = 0; i < productCnt - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < productCnt; j++) {
                if (products[j].unique_id < products[minIndex].unique_id) {
                    minIndex = j;
                }
            }
            // Swap the products at i and minIndex
            Product temp = products[minIndex];
            products[minIndex] = products[i];
            products[i] = temp;
        }
    }

    // searches for a product by its ID using binary search
    int binarySearch(int id) {
        sortProductsById(); // sorts the products by id

        int left = 0;
        int right = productCnt - 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (products[mid].unique_id == id) {
                return mid; // return the index if found
            } else if (products[mid].unique_id < id) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1; // not found
    }

    // displays all inventory products
    void displayInventory() {
        for (int i = 0; i < productCnt; i++) {
            cout << "ID: " << products[i].unique_id << ", Price: " << products[i].price << '\n';
        }
    }
};

int main() {
    Inventory inventory;

    int total_products;
    cout << "How many products you want to add? ";
    cin >> total_products;

    if (total_products > 0) {
        while (total_products--) {
            int id, price;
            cout << "Enter product id, price: ";
            cin >> id >> price;
            inventory.addProduct(id, price);
        }
    } else {
        cout << "Invalid number!\n";
    }

    cout << "Inventory after adding products:\n";
    inventory.displayInventory();

    inventory.sortProductsById();
    cout << "\nInventory after sorting by price:\n";
    inventory.displayInventory();

    int searchId;
    cout << "Enter id to search the product: ";
    cin >> searchId;
    int index = inventory.binarySearch(searchId);

    if (index != -1) {
        cout << "\nProduct found - ID: " << inventory.products[index].unique_id
             << ", Price: " << inventory.products[index].price << '\n';
    } else {
        cout << "\nProduct with ID " << searchId << " not found.\n";
    }

    int removeProductById;
    cout << "Enter the product id to remove the product: ";
    cin >> removeProductById;

    inventory.removeProduct(removeProductById);
    cout << "\nInventory after removing product with ID " << removeProductById << "\n";
    inventory.displayInventory();

    return EXIT_SUCCESS;
}
