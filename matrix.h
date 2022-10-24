#include <stdint.h>

void matrix_init();
void RST(char c);
void SB(char c);
void LAT(char c);
void SCK(char c);
void SDA(char c);
void ROW0(char c);
void ROW1(char c);
void ROW2(char c);
void ROW3(char c);
void ROW4(char c);
void ROW5(char c);
void ROW6(char c);
void ROW7(char c);
void pulse_SCK();
void pulse_LAT();
void deactivate_rows();
void activate_row(int row);
void send_byte(uint8_t val, int bank);

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;