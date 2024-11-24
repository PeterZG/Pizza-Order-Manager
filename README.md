
# Pizza Order Manager - CS_Pizzeria

This project was part of the COMP1511 course at UNSW. It simulates the operations of a pizzeria, including managing orders, tracking ingredients, and calculating profits. Originally submitted in 2021 T3, it has been refined into a standalone project for demonstration purposes.

## Features

1. **Order Management**
   - Add customer orders with details like customer name, pizza type, price, and preparation time.
   - Print all orders in the pizzeria.
   - Select, modify, and remove orders.

2. **Ingredient Tracking**
   - Add ingredients to specific orders.
   - Maintain stock levels for the pizzeria.
   - Refill stock and validate ingredient sufficiency for orders.

3. **Profit Calculation**
   - Compute total profit from each order by subtracting ingredient costs.

4. **File Operations**
   - Save order details and ingredient lists to files.
   - Load ingredients from files back into the system.

5. **Interactive Commands**
   - Includes a command-line interface for testing and interaction.

## Technology Stack

- **Programming Language**: C
- **Memory Management**: Manual with `malloc` and `free`
- **Data Structures**: Linked lists for managing orders and stock
- **File I/O**: Read and write ingredient data from files
- **Development Environment**: Tested on Linux-based systems

## File Structure

- `main.c`: Entry point for the program with command-line interaction.
- `pizzeria.c`: Core implementation of the pizzeria's functionality.
- `pizzeria.h`: Header file defining the data structures and function prototypes.
- `save_string.c` & `save_string.h`: Utility functions for saving and loading data from files.
- Other helper functions and constants used throughout the program.

## Usage

1. Compile the program using the following command:
   ```bash
   gcc -o cs_pizzeria main.c pizzeria.c save_string.c
   ```
   
2. Run the program:
   ```bash
   ./cs_pizzeria
   ```

3. Use the following commands within the program:
   - `o <customer_name> <pizza_name> <price> <time_allowed>`: Add an order.
   - `p`: Print all orders.
   - `>`: Select the next order.
   - `<`: Select the previous order.
   - `i <ingredient_name> <amount> <price>`: Add an ingredient to the current order.
   - `t`: Calculate total profit for the current order.
   - `c`: Cancel the current order.
   - `s`: Print the current stock.
   - `r <ingredient_name> <amount> <price>`: Refill stock.
   - `S <file_name>`: Save ingredients of the current order to a file.
   - `L <file_name>`: Load ingredients from a file into the current order.
   - `q`: Quit the program.

4. View help at any time using the `h` command.

## Example

To simulate basic pizzeria operations:

1. Add an order:
   ```
   o Alice Margherita 15.50 20
   ```

2. Add ingredients to the order:
   ```
   i Tomato 3 0.50
   ```

3. Refill stock:
   ```
   r Cheese 10 1.00
   ```

4. Check profit:
   ```
   t
   ```

## Acknowledgments

This project was inspired by coursework for **COMP1511** at UNSW. Original concepts and ideas were refined into this standalone demonstration.
