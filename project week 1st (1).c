#include <stdio.h>
#include <string.h>

struct Product {
    int productId;
    char name[30];
    int quantity;
    float price;
    float total;
};

int main() {
    struct Product p[5];
    FILE *fp;
    int i, searchId, found = 0;
    float grandTotal = 0;

    // ----------- Input Product Details -----------
    printf("Enter details of 5 products:\n");
    for (i = 0; i < 5; i++) {
        printf("\nProduct %d\n", i + 1);
        printf("Product ID: ");
        scanf("%d", &p[i].productId);

        printf("Product Name: ");
        scanf("%s", p[i].name);

        printf("Quantity: ");
        scanf("%d", &p[i].quantity);

        printf("Price: ");
        scanf("%f", &p[i].price);

        p[i].total = p[i].quantity * p[i].price;
    }

    // ----------- Write Data to File -----------
    fp = fopen("products.txt", "w");
    for (i = 0; i < 5; i++) {
        fprintf(fp, "%d %s %d %.2f %.2f\n",
                p[i].productId,
                p[i].name,
                p[i].quantity,
                p[i].price,
                p[i].total);
    }
    fclose(fp);

    // ----------- Read Data from File -----------
    fp = fopen("products.txt", "r");
    printf("\n\n---------------- Product Details ----------------\n");
    printf("ID\tName\tQty\tPrice\tTotal\n");
    printf("------------------------------------------------\n");

    while (fscanf(fp, "%d %s %d %f %f",
                  &p[0].productId,
                  p[0].name,
                  &p[0].quantity,
                  &p[0].price,
                  &p[0].total) != EOF) {

        printf("%d\t%s\t%d\t%.2f\t%.2f\n",
               p[0].productId,
               p[0].name,
               p[0].quantity,
               p[0].price,
               p[0].total);

        grandTotal += p[0].total;
    }
    fclose(fp);

    printf("------------------------------------------------\n");
    printf("Total Bill Amount: %.2f\n", grandTotal);

    // ----------- Search Product -----------
    printf("\nEnter Product ID to search: ");
    scanf("%d", &searchId);

    fp = fopen("products.txt", "r");
    while (fscanf(fp, "%d %s %d %f %f",
                  &p[0].productId,
                  p[0].name,
                  &p[0].quantity,
                  &p[0].price,
                  &p[0].total) != EOF) {

        if (p[0].productId == searchId) {
            printf("\nProduct Found!\n");
            printf("ID: %d\nName: %s\nQuantity: %d\nPrice: %.2f\nTotal: %.2f\n",
                   p[0].productId,
                   p[0].name,
                   p[0].quantity,
                   p[0].price,
                   p[0].total);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nProduct not found!\n");

    fclose(fp);
    return 0;
}