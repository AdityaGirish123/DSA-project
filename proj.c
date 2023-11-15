#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char category[100];
    char name[100];
    int price;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct CartNode {
    char name[100];
    int price;
    struct CartNode* next;
} CartNode;

Node* createTreeNode(int price, char* category, char* name) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->price = price;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    strcpy(newNode->category, category);
    strcpy(newNode->name, name);
    return newNode;
}

Node* insertTreeNode(Node* root, int price, char* category, char* name) {
    if (root == NULL) {
        return createTreeNode(price, category, name);
    }

    if (price < root->price) {
        root->left = insertTreeNode(root->left, price, category, name);
        root->left->parent = root;
    } else {
        root->right = insertTreeNode(root->right, price, category, name);
        root->right->parent = root;
    }

    return root;
}

Node* leftmostNODE(Node* root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* rightmostNODE(Node* root) {
    while (root != NULL && root->right != NULL) {
        root = root->right;
    }
    return root;
}

Node* nextNode(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->right != NULL) {
        return leftmostNODE(root->right);
    }

    Node* parent = root->parent;
    while (parent != NULL && root == parent->right) {
        root = parent;
        parent = parent->parent;
    }

    return parent;
}

Node* previousNode(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left != NULL) {
        return rightmostNODE(root->left);
    }

    Node* parent = root->parent;
    while (parent != NULL && root == parent->left) {
        root = parent;
        parent = parent->parent;
    }

    return parent;
}

void displayCart(CartNode* cart) {
    if (cart == NULL) {
        printf("Cart is empty.\n");
        return;
    }

    printf("Cart Contents:\n");
    while (cart != NULL) {
        printf("Product: %s, Price: %d\n", cart->name, cart->price);
        cart = cart->next;
    }
}

CartNode* addToCart(CartNode* cart, Node* product) {
    CartNode* newCartItem = (CartNode*)malloc(sizeof(CartNode));
    if (newCartItem == NULL) {
        fprintf(stderr, "Memory allocation for cart item failed.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newCartItem->name, product->name);
    newCartItem->price = product->price;
    newCartItem->next = cart;

    return newCartItem;
}

void displayProducts(Node* root) 
{
    if (root != NULL) {
        displayProducts(root->left);
        printf("Category: %s, Product: %s, Price: %d\n", root->category, root->name, root->price);
        displayProducts(root->right);
    }
}


int main() {

    Node* categoryRoots[5];

    // Initialize roots to NULL
    for (int i = 0; i < 5; i++) {
        categoryRoots[i] = NULL;
    }

    // Electronics
    categoryRoots[0] = insertTreeNode(NULL, 1299, "Electronics", "MacBook Air M1");
    insertTreeNode(categoryRoots[0], 799, "Electronics", "Samsung Galaxy S21");
    insertTreeNode(categoryRoots[0], 349, "Electronics", "Sony WH-1000XM4 Wireless Headphones");
    insertTreeNode(categoryRoots[0], 49.99, "Electronics", "Amazon Echo Dot (4th Gen)");
    insertTreeNode(categoryRoots[0], 699, "Electronics", "Nikon D5600 DSLR Camera");

    // Clothing and Fashion
    categoryRoots[1] = insertTreeNode(NULL, 59.99, "Clothing", "Levi's 501 Original Fit Jeans");
    insertTreeNode(categoryRoots[1], 25, "Clothing", "Adidas Originals Men's Trefoil Tee");
    insertTreeNode(categoryRoots[1], 39.99, "Clothing", "Women's Long Sleeve V-Neck Sweater");
    insertTreeNode(categoryRoots[1], 55, "Clothing", "Converse Chuck Taylor All Star Low Top Sneakers");
    insertTreeNode(categoryRoots[1], 69.99, "Clothing", "Men's Hooded Fleece Jacket");

    // Books and Audible
    categoryRoots[2] = insertTreeNode(NULL, 9.99, "Books and Audible", "The Great Gatsby by F. Scott Fitzgerald (Paperback)");
    insertTreeNode(categoryRoots[2], 14.99, "Books and Audible", "Educated by Tara Westover (Kindle Edition)");
    insertTreeNode(categoryRoots[2], 24.95, "Books and Audible", "Sapiens: A Brief History of Humankind by Yuval Noah Harari (Audiobook)");
    insertTreeNode(categoryRoots[2], 19.59, "Books and Audible", "Becoming by Michelle Obama (Hardcover)");
    insertTreeNode(categoryRoots[2], 27.99, "Books and Audible", "Atomic Habits by James Clear (Audible Audiobook)");

    // Home and Kitchen
    categoryRoots[3] = insertTreeNode(NULL, 89.99, "Home and Kitchen", "Instant Pot Duo 7-in-1 Electric Pressure Cooker");
    insertTreeNode(categoryRoots[3], 199.99, "Home and Kitchen", "Shark Navigator Lift-Away Professional Vacuum");
    insertTreeNode(categoryRoots[3], 249, "Home and Kitchen", "Nest Learning Thermostat");
    insertTreeNode(categoryRoots[3], 129.99, "Home and Kitchen", "Keurig K-Elite Coffee Maker");
    insertTreeNode(categoryRoots[3], 19.99, "Home and Kitchen", "AmazonBasics Microfiber Sheet Set (Queen)");

    // Health and Personal Care
    categoryRoots[4] = insertTreeNode(NULL, 69.99, "Health and Personal Care", "Philips Sonicare ProtectiveClean Electric Toothbrush");
    insertTreeNode(categoryRoots[4], 16.97, "Health and Personal Care", "Neutrogena Hydro Boost Water Gel Moisturizer");
    insertTreeNode(categoryRoots[4], 149.95, "Health and Personal Care", "Fitbit Charge 4 Fitness and Activity Tracker");
    insertTreeNode(categoryRoots[4], 16.99, "Health and Personal Care", "Nature Made Vitamin D3 2000 IU Softgels");
    insertTreeNode(categoryRoots[4], 21.99, "Health and Personal Care", "Gillette Fusion5 ProGlide Men's Razor");


    for (int i = 0; i < 5; i++) {
        printf("\nProducts under %s:\n", categoryRoots[i]->category);
        displayProducts(categoryRoots[i]);
    }

    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Electronics\n");
        printf("2.  Clothing and Fashion\n");
        printf("3.  Books and Audible\n");
        printf("4.  Home and Kitchen\n");
        printf("5.  Health and Personal Care\n");
        printf("6. Exit\n");


        printf("Enter your choice of category: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 5) 
        {
            displayProducts(categoryRoots[choice - 1]);
            Node* currentNode = leftmostNODE(categoryRoots[choice - 1]);

            if (currentNode != NULL)
            {
                CartNode* cart = NULL;

                while (1) 
                {
                    printf("selected product:\n");
                    printf("Category: %s, Product: %s, Price: %d\n", currentNode->category, currentNode->name, currentNode->price);

                    printf("Press 'n' for Next Node, 'p' for Previous Node, 'a' to Add to Cart, 'v' to View Cart, or 'q' to Quit:\n");
                    char option;
                    scanf(" %c", &option);

                    if (option == 'q') {
                        break;
                    } else if (option == 'n') {
                        currentNode = nextNode(currentNode);
                    } else if (option == 'p') {
                        currentNode = previousNode(currentNode);
                    } else if (option == 'a') {
                        cart = addToCart(cart, currentNode);
                        printf("Added to Cart: %s, Price: %d\n", currentNode->name, currentNode->price);
                    } else if (option == 'v') {
                        displayCart(cart);
                    }
                }

                // Free memory for the cart when done
                while (cart != NULL) {
                    CartNode* temp = cart;
                    cart = cart->next;
                    free(temp);
                }
            } else {
                printf("No products in the selected category.\n");
            }

        } else if (choice == 6) {
            printf("Exit\n");
        } else {
            printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}
