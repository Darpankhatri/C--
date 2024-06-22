#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Item;

Item inventory[MAX_ITEMS];
int itemCount = 0;

void addItem() {
    if (itemCount >= MAX_ITEMS) {
        printf("Inventory is full!\n");
        return;
    }

    Item newItem;
    printf("Enter item ID: ");
    scanf("%d", &newItem.id);

    printf("Enter item name: ");
    scanf(" %[^\n]", newItem.name);  // %[^\n] to read spaces in item name

    printf("Enter item quantity: ");
    scanf("%d", &newItem.quantity);

    printf("Enter item price: ");
    scanf("%f", &newItem.price);

    inventory[itemCount] = newItem;
    itemCount++;

    printf("Item added successfully!\n");
}

void displayItems() {
    if (itemCount == 0) {
        printf("Inventory is empty!\n");
        return;
    }

    printf("\nID\tName\tQuantity\tPrice\n");
    printf("--------------------------------------\n");

    for (int i = 0; i < itemCount; i++) {
        printf("%d\t%s\t%d\t\t%.2f\n", inventory[i].id, inventory[i].name,
               inventory[i].quantity, inventory[i].price);
    }

    printf("--------------------------------------\n");
}

void updateItem() {
    int id, found = 0;

    if (itemCount == 0) {
        printf("Inventory is empty!\n");
        return;
    }

    printf("Enter item ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            printf("Enter new quantity: ");
            scanf("%d", &inventory[i].quantity);

            printf("Enter new price: ");
            scanf("%f", &inventory[i].price);

            found = 1;
            printf("Item updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Item with ID %d not found!\n", id);
    }
}

void deleteItem() {
    int id, found = 0;

    if (itemCount == 0) {
        printf("Inventory is empty!\n");
        return;
    }

    printf("Enter item ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            for (int j = i; j < itemCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            itemCount--;
            found = 1;
            printf("Item deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Item with ID %d not found!\n", id);
    }
}

void saveToFile() {
    FILE *file = fopen("inventory.txt", "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        fprintf(file, "%d %s %d %.2f\n", inventory[i].id, inventory[i].name,
                inventory[i].quantity, inventory[i].price);
    }

    fclose(file);
    printf("Inventory saved to file successfully!\n");
}

void loadFromFile() {
    FILE *file = fopen("inventory.txt", "r");

    if (file == NULL) {
        printf("No existing inventory found. Starting fresh.\n");
        return;
    }

    itemCount = 0;

    while (fscanf(file, "%d %s %d %f", &inventory[itemCount].id,
                  inventory[itemCount].name, &inventory[itemCount].quantity,
                  &inventory[itemCount].price) != EOF) {
        itemCount++;
    }

    fclose(file);
    printf("Inventory loaded from file successfully!\n");
}

int main() {
    int choice;
    loadFromFile();

    while (1) {
        printf("\nInventory Management System\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Update Item\n");
        printf("4. Delete Item\n");
        printf("5. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                displayItems();
                break;
            case 3:
                updateItem();
                break;
            case 4:
                deleteItem();
                break;
            case 5:
                saveToFile();
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}