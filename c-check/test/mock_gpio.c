#include "mock_gpio.h"

int gpio_open_called_value = UNSET;
gpio_handle_t gpio_open(int value)
{
  gpio_open_called_value = value;
  return 0;
}

int gpio_open_called_with()
{
  return gpio_open_called_value;
}

int gpio_pin_input_value = UNSET;
int gpio_pin_input(gpio_handle_t, int value)
{
  gpio_pin_input_value = value;
  return 0;
}
int gpio_pin_input_called_with()
{
  return gpio_pin_input_value;
}

int gpio_pin_pulldown_value = UNSET;
int gpio_pin_pulldown(gpio_handle_t, int value)
{
  gpio_pin_pulldown_value = value;
  return 0;
}
int gpio_pin_pulldown_called_with()
{
  return gpio_pin_pulldown_value;
}

int gpio_pio_output_value = UNSET;
int gpio_pio_output(gpio_handle_t, int value)
{
  gpio_pio_output_value = value;
  return 0;
}
int gpio_pin_output_called_with()
{
  return gpio_pio_output_value;
};

gpio_value_t gpio_pin_get_return = UNSET;
int gpio_pin_get_value = UNSET;
gpio_value_t gpio_pin_get(gpio_handle_t, int value)
{
  gpio_pin_get_value = value;
  return gpio_pin_get_return;
}
void gpio_pin_get_will_return(int, gpio_value_t ret)
{
  gpio_pin_get_return = ret;
}
int gpio_pin_get_called_with()
{
  return gpio_pin_get_value;
}

#define MOCK_SIZE 10
struct pinvalue gpio_pin_set_value[MOCK_SIZE];
int gpio_pin_set_idx = 0;
int gpio_pin_set(gpio_handle_t, int pin, gpio_value_t value)
{
  struct pinvalue *cur;

  if (gpio_pin_set_idx < MOCK_SIZE) {
    cur = &gpio_pin_set_value[gpio_pin_set_idx++];
    cur->pin = pin;
    cur->value = value;
  }
  return 0;
}

struct pinvalue gpio_pin_set_called_with(int idx)
{
  return gpio_pin_set_value[idx];
}

int gpio_pin_set_call_count()
{
  return gpio_pin_set_idx;
}
