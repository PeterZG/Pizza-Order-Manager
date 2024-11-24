// Assignment 2 21T3 COMP1511: CS Pizzeria
// pizzeria.c
//
// Weihou Zeng(z5270202)
// 2021/11/15
//
//
// Version 1.0.0: Release

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pizzeria.h"
#include "save_string.h"

#define NUM 8096
#define NUM_ONE 30

struct ingredient {
    char ingredient_name[MAX_STR_LENGTH];
    int amount;
    double price;
    struct ingredient *next;
};

struct order {
    char customer_name[MAX_STR_LENGTH];
    char pizza_name[MAX_STR_LENGTH];
    double price;
    int time_allowed;
    struct order *next;
    struct ingredient *ingredient_one;
};

struct pizzeria {
    struct order *selected;
    struct order *orders;
    struct ingredient *stock;
};

//////////////////////////////////////////////////////////////////////

// TODO: add prototypes for any helper functions you create here.
// Prints a single order
void print_order(
    int num,
    char *customer,
    char *pizza_name,
    double price,
    int time_allowed
);

// Prints an ingredient given the name, amount and price in the required format.
// This will be needed for stage 2.
void print_ingredient(char *name, int amount, double price);

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

struct pizzeria *create_pizzeria() {
    // Allocates memory to store a `struct pizzeria` and returns a pointer to
    // it. The variable `new` holds this pointer!
    struct pizzeria *new_pizza_hut = malloc(sizeof(struct pizzeria));

    new_pizza_hut->orders = NULL;
    new_pizza_hut->selected = NULL;
    new_pizza_hut->stock = NULL;

    return new_pizza_hut;
}
//The customer's name,
//The pizza's name,
//The price they will pay for the pizza and
//The time allowed to cook the pizza in.
int add_order(struct pizzeria *pizzeria, char *customer, 
char *pizza_name, double price, int time_allowed) {
    //An order is a customer's request to the pizzeria and needs to be stored
    //set boundary for price and time
    if (price < 0) {
        return INVALID_PRICE;
    }
    if (time_allowed <= 0) {
        return INVALID_TIME;
    }
    struct order *newfirst = malloc(sizeof(struct order));

    strcpy(newfirst->customer_name, customer);
    strcpy(newfirst->pizza_name, pizza_name);

    newfirst->price = price;
    newfirst->time_allowed = time_allowed;
    newfirst->next = NULL;
    newfirst->ingredient_one = NULL;

    if (pizzeria->orders == NULL) {
        pizzeria->orders = newfirst;
    }

    else if (pizzeria->orders != NULL) {
        struct order *point = pizzeria->orders;
        if (point->next != NULL) {
            while (1) {
                point = point->next;
                if (point->next == NULL)
                    break;
            }
        }        
        point->next = newfirst;
    }

    return SUCCESS;
}

void print_all_orders(struct pizzeria *pizzeria) {
    //Printing all the orders
    struct order *point = pizzeria->orders;
    int num = 1;
    if (point != NULL) {
        while (1) {
            print_order(num, point->customer_name, point->pizza_name, 
            point->price, point->time_allowed);
            num += 1;
            point = point->next;
            if (point == NULL)
                break;
        }
    }   
    print_selected_order(pizzeria);
    return;
}

int next_deadline(struct pizzeria *pizzeria) {
    //To tell the chefs what is the shortest time allowed among all orders in the pizzeria
    struct order *point = pizzeria->orders;
    if (point == NULL) {
        return INVALID_CALL;
    }
    int low = point->time_allowed;
    if (point != NULL) {
        while (1) {
            if (low > point->time_allowed) {
                low = point->time_allowed;
            }
            point = point->next;
            if (point == NULL)
                break;    
        }
    }
    return low;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////


void select_next_order(struct pizzeria *pizzeria) {
    //select the order which you want to make changes to
    if (pizzeria->selected == NULL) {
        pizzeria->selected=pizzeria->orders;
    }

    else {
        pizzeria->selected = pizzeria->selected->next;
    }

}

void select_previous_order(struct pizzeria *pizzeria) {
    //select the prvious order: if the selected order is the third order in the list, 
    //after this function call, 
    //the selected order should become the second order in the list.
    struct order *p = pizzeria->orders;

    if (pizzeria->selected == pizzeria->orders) {
        pizzeria->selected = NULL;
    }

    else if (pizzeria->selected == NULL) {
        if (p->next != NULL)
        while (1) {
            p = p->next;
            if (p->next == NULL)
                break;
        }
        pizzeria->selected = p;
    }

    else {
        if (p->next != pizzeria->selected)
        while (1) {
            p = p->next;
            if (p->next == pizzeria->selected)
                break;
        }
        pizzeria->selected = p;
    }
    return;
}

void print_selected_order(struct pizzeria *pizzeria) {
    //prints the number of the selected order 
    //and the ingredients within the selected order.
    if (pizzeria->selected == NULL) {
        printf("\nNo selected order.\n");
    }

    else {
        printf("\nThe selected order is %s's %s pizza ($%.2lf) due in %d minutes.\n",
        pizzeria->selected->customer_name, pizzeria->selected->pizza_name, 
        pizzeria->selected->price, pizzeria->selected->time_allowed);
        struct ingredient *point = pizzeria->selected->ingredient_one;

        if (point != NULL)
        while (1) {
            print_ingredient(point->ingredient_name,point->amount,point->price);
            point = point->next;
            if (point == NULL)
                break;
        }
    }
}

int add_ingredient(struct pizzeria *pizzeria, 
char *ingredient_name, int amount, double price) {
    //Add an ingredient to the selected order.
    if (pizzeria->selected == NULL) {
        return INVALID_ORDER;
    }

    if (price < 0) {
        return INVALID_PRICE;
    }

    if (amount <= 0) {
        return INVALID_AMOUNT;
    }

    struct ingredient *new_one = malloc(sizeof(struct ingredient));
    strcpy(new_one->ingredient_name, ingredient_name);

    new_one->price = price;
    new_one->next = NULL;
    new_one->amount = amount;

    if (pizzeria->selected->ingredient_one == NULL) {
        pizzeria->selected->ingredient_one = new_one;
        return SUCCESS;
    }

    else {
        struct ingredient *p = pizzeria->selected->ingredient_one;
        if (strcmp(p->ingredient_name, new_one->ingredient_name) == 0) {
            free(new_one);
            p->amount += amount;
            return SUCCESS;
        }

        else if (strcmp(p->ingredient_name, new_one->ingredient_name) > 0) {
            if (p == pizzeria->selected->ingredient_one) {
                new_one->next = p;
                pizzeria->selected->ingredient_one = new_one;
                return SUCCESS;
            }
        }

        if (p->next != NULL)
        while (1) {
            if (strcmp(p->next->ingredient_name, new_one->ingredient_name) == 0) {
                p->next->amount += amount;
                free(new_one);
                return SUCCESS;
            }

            else if (strcmp(p->next->ingredient_name, new_one->ingredient_name) > 0) {
                struct ingredient *quote = p->next;
                p->next = new_one;
                new_one->next = quote;
                return SUCCESS;
            }
            p = p->next;

            if (p->next == NULL)
                break;
        }
        p->next = new_one;
        return SUCCESS;
    }
}

double calculate_total_profit(struct pizzeria *pizzeria) {
    //Calculate the total profit of the selected order by calculating the expenses of the 
    //ingredients and subtracting it from the price the customer is paying
    if (pizzeria->selected == NULL) {
        return INVALID_ORDER;
    }

    double number = pizzeria->selected->price;
    struct ingredient *p = pizzeria->selected->ingredient_one;

    if (p != NULL)
    while (1) {
        number = number - p->amount*p->price;
        p = p->next;
        if (p == NULL)
            break;
    }
    return number;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////


int cancel_order(struct pizzeria *pizzeria) {
    //free the selected order and its associated memory 
    if (pizzeria->selected == NULL) {
        return INVALID_ORDER;
    }

    struct ingredient *p = pizzeria->selected->ingredient_one;

    if (p != NULL)
    while (1) {
        struct ingredient *quote = p->next;
        free(p);
        p = quote;
        if (p == NULL)
            break;
    }

    struct order *point_form = pizzeria->orders;

    if (pizzeria->orders == pizzeria->selected) {
        pizzeria->orders = pizzeria->orders->next;
    }

    else {
        if (point_form->next != pizzeria->selected)
        while (1) {
            point_form = point_form->next;
            if (point_form->next == pizzeria->selected)
                break;
        }
        point_form->next = pizzeria->selected->next;
    }

    struct order *pose = pizzeria->selected;
    select_next_order(pizzeria);
    free(pose);
    return SUCCESS;
}

void free_pizzeria(struct pizzeria *pizzeria) {
    //free the pizzeria passed in and its associated memory
    pizzeria->selected = pizzeria->orders;
    while (pizzeria->selected != NULL) {
        cancel_order(pizzeria);
    }

    for (struct ingredient *p = pizzeria->stock;p != NULL;) {
        struct ingredient *quote = p->next;
        free(p);
        p = quote;
    }

    free(pizzeria);
    pizzeria = NULL;
}

int refill_stock(struct pizzeria *pizzeria, char *ingredient_name, 
int amount, double price) {
    //insert ingredients into the stock 
    //The stock is a one dimensional linked list of ingredients 
    //which keeps track of how many ingredients there are in the pizzeria
    if (price < 0) {
        return INVALID_PRICE;
    }
    if (amount <= 0) {
        return INVALID_AMOUNT;
    }

    struct ingredient *new_one = malloc(sizeof(struct ingredient));
    strcpy(new_one->ingredient_name, ingredient_name);
    new_one->price = price;
    new_one->next = NULL;
    new_one->amount = amount;

    if (pizzeria->stock == NULL) {
        pizzeria->stock = new_one;
        return SUCCESS;
    }

    else {
        struct ingredient *p = pizzeria->stock;
        if (strcmp(p->ingredient_name, new_one->ingredient_name) == 0) {
            p->amount += amount;
            free(new_one);
            return SUCCESS;
        }
        else if (strcmp(p->ingredient_name, new_one->ingredient_name) > 0) {
            if (p == pizzeria->stock) {
                new_one->next = p;
                pizzeria->stock = new_one;
                return SUCCESS;
            }
        }

        if (p->next != NULL)
        while (1) {
            if (strcmp(p->next->ingredient_name, new_one->ingredient_name) == 0) {
                p->next->amount += amount;
                free(new_one);
                return SUCCESS;
            }
            else if (strcmp(p->next->ingredient_name, new_one->ingredient_name) > 0) {
                struct ingredient *quote = p->next;
                p->next = new_one;
                new_one->next = quote;
                return SUCCESS;
            }
            p = p->next;
            if (p->next == NULL)
                break;
        }
        p->next = new_one;
        return SUCCESS;
    }
    return SUCCESS;
}

void print_stock(struct pizzeria *pizzeria) {
    //print all the in-stock ingredients in the pizzeria
    struct ingredient *p = pizzeria->stock;
    printf("  The stock contains:\n");
    if (p != NULL)
    while (1) {
        print_ingredient(p->ingredient_name, 
        p->amount, p->price);
        p = p->next;
        if (p == NULL)
            break;
    }
    return;
}

int can_complete_order(struct pizzeria *pizzeria) {
    //The chefs of the pizzeria need to know if 
    //they can complete the order with their current stock
    if (pizzeria->selected == NULL || pizzeria->selected->ingredient_one == NULL) {
        return INVALID_ORDER;
    }

    struct ingredient *p = pizzeria->selected->ingredient_one;
    struct ingredient *quote = pizzeria->stock;

    while (p != NULL) {
        while (quote && strcmp(quote->ingredient_name, p->ingredient_name)) {
            quote = quote->next;
        }   
        if (quote == NULL || quote->amount < p->amount) {
            return INSUFFICIENT_STOCK;
        }
        p = p->next;
    }
    return SUCCESS;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

int complete_order(struct pizzeria *pizzeria) {
    //complete the selected order if it is possible 
    //and adjust the stock based on this completion
    if (pizzeria->selected == NULL || pizzeria->selected->ingredient_one == NULL) {
        return INVALID_ORDER;
    }

    struct ingredient *p = pizzeria->selected->ingredient_one;
    struct ingredient *quote = pizzeria->stock;

    if (p != NULL)
    while (1) {
        while (quote && strcmp(quote->ingredient_name, p->ingredient_name)) {
            quote = quote->next;
        }
        if (quote == NULL || quote->amount < p->amount) {
            return INSUFFICIENT_STOCK;
        }
        p = p->next;
        if (p == NULL)
            break;
    }

    p = pizzeria->selected->ingredient_one;
    quote = pizzeria->stock;

    while (p != NULL) {
        while (quote && strcmp(quote->ingredient_name, p->ingredient_name)) {
            quote = quote->next;
        }
        quote->amount -= p->amount;
        p = p->next;
    }

    quote = pizzeria->stock;

    while (quote->amount == 0) {
        pizzeria->stock = quote->next;
        free(quote);
        quote = pizzeria->stock;
    }

    while (quote->next != NULL) {
        if (quote->next->amount == 0) {
            p = quote->next;
            quote->next = quote->next->next;
            free(p);
        }
        else {
            quote = quote->next;
        }
    }
    cancel_order(pizzeria);
    return SUCCESS;
}

int save_ingredients(struct pizzeria *pizzeria, char *file_name) {
    //save the ingredients of the selected ordered as a string to a file
    //To save a given string into a file
    char load_the_string[NUM];
    int character_counts = 0;
    if (pizzeria->selected == NULL) {
        return INVALID_ORDER;
    }

    struct ingredient *p = pizzeria->selected->ingredient_one;

    if (p != NULL)
    while (1) {
        if (character_counts == 0 ) {
            character_counts += sprintf(load_the_string + character_counts, 
            "name=%s ", p->ingredient_name);
        } 
        else {
            character_counts += sprintf(load_the_string + character_counts, 
            "name=%s ", p->ingredient_name);
        }
        character_counts += sprintf(load_the_string + character_counts, 
        "amount=%d ", p->amount);

        character_counts += sprintf(load_the_string + character_counts, 
        "price=%.2lf [", p->price);

        character_counts += sprintf(load_the_string + character_counts, 
        "%d ", character_counts);

        p = p->next;

        if (p == NULL) 
            break;
    }

    save_string(file_name, load_the_string);
    return SUCCESS;
}

int load_ingredients(struct pizzeria *pizzeria, char *file_name) {
    //Add the ingredients of the file with the given name to the currently selected order
    //To load the file of the given name into a string which it returns
    char *load_the_string = load_string(file_name);
    char name_one[NUM_ONE];
    int amount_one;
    float price_one;

    int position = 0;
    int j = strlen(load_the_string);
    int number_first = 3;
    int number_second = 4;
    int number_third = 100;

    if (position <= j - number_first) 
    while (1) {
        sscanf(load_the_string + position, "name=%s amount=%d price=%f [%d", 
        name_one, &amount_one, &price_one, &position);
        add_ingredient(pizzeria, name_one, amount_one, price_one);
        
        if (position < number_third) {
            position += number_first;
        } 

        else {
            position += number_second;
        }

        if (position > j - number_first)
            break;
    }
    free(load_the_string);
    return SUCCESS;
}

////////////////////////////////////////////////////////////////////////
//               HELPER FUNCTIONS - Add your own here                 //
////////////////////////////////////////////////////////////////////////

// Prints a single order
//
// `print_order` will be given the parameters:
// - `num` -- the integer that represents which order it is sequentially.
// - `customer` -- the name of the customer for that order.
// - `pizza_name` -- the pizza the customer ordered.
// - `price` -- the price the customer is paying for the pizza.
// - `time_allowed` -- the time the customer will wait for the order.
//
// `print_order` assumes all parameters are valid.
//
// `print_order` returns nothing.
//
// This will be needed for Stage 1.
void print_order(
    int num,
    char *customer,
    char *pizza_name,
    double price,
    int time_allowed
) {

    printf("%02d: %s ordered a %s pizza ($%.2lf) due in %d minutes.\n",
        num, customer, pizza_name, price, time_allowed);

    return;
}

// Prints a single ingredient
//
// `print_ingredient` will be given the parameters:
// - `name` -- the string which contains the ingredient's name.
// - `amount` -- how many of the ingredient we either need or have.
// - `price` -- the price the ingredient costs.
//
// `print_ingredient` assumes all parameters are valid.
//
// `print_ingredient` returns nothing.
//
// This will be needed for Stage 2.
void print_ingredient(char *name, int amount, double price) {

    printf("   %s: %d @ $%.2lf\n", name, amount, price);
}


