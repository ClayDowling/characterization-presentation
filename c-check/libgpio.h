/* libgpio is specific to FreeBSD.  This library allows me to include
 * it when we're compiling for the FreeBSD target, but add declarations
 * for the appropriate mocks in the development environment.
 */

#ifdef __FreeBSD__
#include <libgpio.h>
#else
typedef int gpio_handle_t;
typedef int gpio_value_t;

#define GPIO_PIN_HIGH 1
#define GPIO_PIN_LOW 0

#define GPIO_VALUE_LOW 0
#define GPIO_VALUE_HIGH 1

#define GPIO_INVALID_HANDLE -1

gpio_handle_t gpio_open(int);

int gpio_pin_input(gpio_handle_t, int);

int gpio_pin_pulldown(gpio_handle_t, int);

int gpio_pin_output(gpio_handle_t, int);

gpio_value_t gpio_pin_get(gpio_handle_t, int);

int gpio_pin_set(gpio_handle_t, int, int);

#endif
