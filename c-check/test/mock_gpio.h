/* Test doubles for FreeBSD gpio library
 *
 */

#ifndef _MOCK_GPIO_H_
#define _MOCK_GPIO_H_

typedef int gpio_handle_t;
typedef int gpio_value_t;

#define GPIO_PIN_HIGH 1
#define GPIO_PIN_LOW 0

#define GPIO_VALUE_LOW 0
#define GPIO_VALUE_HIGH 1

#define GPIO_INVALID_HANDLE -1

#define UNSET -1

gpio_handle_t gpio_open(int);
int gpio_open_called_with();

int gpio_pin_input(gpio_handle_t, int);
int gpio_pin_input_called_with();

int gpio_pin_pulldown(gpio_handle_t, int);
int gpio_pin_pulldown_called_with();

int gpio_pin_output(gpio_handle_t, int);
int gpio_pin_output_called_with();

gpio_value_t gpio_pin_get(gpio_handle_t, int);
void gpio_pin_get_will_return(int, gpio_value_t*);
int gpio_pin_get_called_with();

int gpio_pin_set(gpio_handle_t, int, int);

struct pinvalue {
  int pin;
  int value;
};

struct pinvalue gpio_pin_set_called_with(int idx);
int gpio_pin_set_call_count();

void gpio_reset_mocks();

#endif
