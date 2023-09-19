/*******************************************************************************
   Autor:       Radek Duchon (xducho07)
   Zmeny:       99 %
   datum:       17. 12. 2019 
*******************************************************************************/

#include <fitkitlib.h>
#include <keyboard/keyboard.h>
#include <lcd/display.h>
#include <stdlib.h>
#include <string.h>

// Pozice na druhem radku
#define pos (lcd_cursor_addr - 16)

// Dalsi/Predchozi vyznam pro tlacitka A/B
#define next(c) (c == 'A')
#define back(c) (c == 'B')

// Posun kursor na druhy radek
#define second_line() lcd_cursor_addr = 16

// Posouva kursor na dalsi pozici (na druhem radku), pokud mozno, pracuje s lokalnim polem number
#define after() do { if (number[pos]) LCD_append_char(number[pos]); } while (0)

// Posouva kursor na dalsi pozici pokud mozno, pracuje s globalnim polem text
#define after_c() do { if (text[lcd_cursor_addr]) LCD_append_char(text[lcd_cursor_addr]); } while (0)

// Posouva kursor na predchozi pozici (na druhem radku), pokud mozno, pracuje s lokalnim polem number
#define before() do {\
		if (pos > 1) {\
			lcd_cursor_addr -= 2;\
			LCD_append_char(number[pos]);\
		} else if (pos == 1) {\
		      	lcd_cursor_addr = 0;\
		      	LCD_append_string("Zadejte posun:  ");\
		}\
	} while (0)

// Posouva kursor na predchozi pozici, pokud mozno, pracuje s globalnim polem text
#define before_c() do {\
		if (lcd_cursor_addr > 1) {\
			lcd_cursor_addr -= 2;\
			LCD_append_char(text[lcd_cursor_addr]);\
		} else if (lcd_cursor_addr == 1) {\
		      	lcd_cursor_addr = 0;\
		}\
	} while (0)

// Udela zpozdeni pro blikani led. Nacte znak z klavesnice a skoci na "where" pokud byla stisknuta klavesa "predchozi"
#define wait(where) do {\
	    	delay_ms(10);\
		if (++cnt == 100) {\
			cnt = 0;\
	  		flip_led_d6();\
    		}\
	    	c = keyboard_idle();\
    		if (back(c))\
			goto where;\
	} while (0)


extern int lcd_cursor_addr; ///< Pozice kurzoru na LCD (delka zapsaneho retezce)
int cnt; //counter for led
int i; //index
char text[41]; //array for text


/*******************************************************************************
 * Vypis uzivatelske napovedy (funkce se vola pri vykonavani prikazu "help")
*******************************************************************************/
void print_user_help(void)
{
}


/*******************************************************************************
 * Obsluha klavesnice
*******************************************************************************/
char keyboard_idle()
{
  char ch = key_decode(read_word_keyboard_4x4());
  static char last_ch = 0;
  return ch != last_ch ? last_ch = ch : 0;
}


/*******************************************************************************
 * Dekodovani a vykonani uzivatelskych prikazu
*******************************************************************************/
unsigned char decode_user_cmd(char *cmd_ucase, char *cmd)
{
  return CMD_UNKNOWN;
}

/*******************************************************************************
 * Inicializace periferii/komponent po naprogramovani FPGA
*******************************************************************************/
void fpga_initialized()
{
  LCD_init();
}

/*******************************************************************************
 * simulace tlacitek telefonu
*******************************************************************************/
char mobile(char act, char c)
{
  if (act >= 'a' && act <= 'z' || act == 0) {
    switch (c) {
      case '0':
        return act == ' ' ? '0' : ' ';
      case '1':
        return act == '.' ? '!' : act == '!' ? '?' : act == '?' ? ':' : act == ':' ? ')' : act == ')' ? '(' : act == '(' ? '.' : 1;
      case '2':
        return act == 'a' ? 'b' : act == 'b' ? 'c' : act == 'c' ? '2' : 'a';
      case '3':
        return act == 'd' ? 'e' : act == 'e' ? 'f' : act == 'f' ? '3' : 'd';
      case '4':
        return act == 'g' ? 'h' : act == 'h' ? 'i' : act == 'i' ? '4' : 'g';
      case '5':
        return act == 'j' ? 'k' : act == 'k' ? 'l' : act == 'l' ? '5' : 'j';
      case '6':
        return act == 'm' ? 'n' : act == 'n' ? 'o' : act == 'o' ? '6' : 'm';
      case '7':
        return act == 'p' ? 'q' : act == 'q' ? 'r' : act == 'r' ? 's' : act == 's' ? '7' : 'p';
      case '8':
        return act == 't' ? 'u' : act == 'u' ? 'v' : act == 'v' ? '8' : 't';
      case '9':
        return act == 'w' ? 'x' : act == 'x' ? 'y' : act == 'y' ? 'z' : act == 'z' ? '9' : 'w';
      default:
	return ' ';
    }
  } else {
    switch (c) {
      case '0':
        return act == ' ' ? '0' : ' ';
      case '1':
        return act == '.' ? '!' : act == '!' ? '?' : act == '?' ? ':' : act == ':' ? ')' : act == ')' ? '(' : act == '(' ? '.' : 1;
      case '2':
        return act == 'A' ? 'B' : act == 'B' ? 'C' : act == 'C' ? '2' : 'A';
      case '3':
        return act == 'D' ? 'E' : act == 'E' ? 'F' : act == 'F' ? '3' : 'D';
      case '4':
        return act == 'G' ? 'H' : act == 'H' ? 'I' : act == 'I' ? '4' : 'G';
      case '5':
        return act == 'J' ? 'K' : act == 'K' ? 'L' : act == 'L' ? '5' : 'J';
      case '6':
        return act == 'M' ? 'N' : act == 'N' ? 'O' : act == 'O' ? '6' : 'M';
      case '7':
	return act == 'P' ? 'Q' : act == 'Q' ? 'R' : act == 'R' ? 'S' : act == 'S' ? '7' : 'P';
      case '8':
        return act == 'T' ? 'U' : act == 'U' ? 'V' : act == 'V' ? '8' : 'T';
      case '9':
        return act == 'W' ? 'X' : act == 'X' ? 'Y' : act == 'Y' ? 'Z' : act == 'Z' ? '9' : 'W';
      default:
	return ' ';
    }
  }
}

/*******************************************************************************
 * Vypise za/desifrovanou zpravu na displej
*******************************************************************************/
void code(int hash, int encode)
{
  char c;
  char b = 0;
BONUS:
  if (b < 0)
    b += 26;
  LCD_clear();
  for (i = 0; text[i]; ++i) {
    if (i >= 32)
      LCD_rotate();
    if (text[i] >= 'a' && text[i] <= 'z') {
      LCD_append_char((text[i] - 'a' + 26 + (hash * encode) + b) % 26 + 'a');
    } else if (text[i] >= 'A' && text[i] <= 'Z') {
      LCD_append_char((text[i] - 'A' + 26 + (hash * encode) + b) % 26 + 'A');
    } else
      LCD_append_char(text[i]);
  }
  while (1) {
    delay_ms(10);
    if (++cnt == 100) {
      cnt = 0;
      flip_led_d6();
    }
    c = keyboard_idle();
    // Navrat k predeslemu kroku
    if (back(c))
      return;
    // Posun doleva
    if (c == '*')
      LCD_send_cmd(LCD_CURSOR_DISPLAY_SHIFT | LCD_SHIFT_DISPLAY | LCD_SHIFT_DIR_RIGHT, 0);
    // Posun doprava
    else if (c == '#')
      LCD_rotate();
    // Presifrovani + 1
    else if (c == 'A') {
      ++b;
      goto BONUS;
    // Presifrovani - 1
    } else if (c == 'C') {
      --b;
      goto BONUS;
    }
  }
}

/*******************************************************************************
 * Plni pole pro zasifrovani/desifrovani
*******************************************************************************/
void caesar(int hash, int encode)
{
  char c;
  int idx;
CAESAR:
  idx = strlen(text) - lcd_cursor_addr;
  LCD_clear();
  for (i = 0; text[i]; ++i) {
    if (i >= 32)
      LCD_rotate();
    LCD_append_char(text[i]);
  }
  while (--idx >= 0)
    before_c();

  idx = strlen(text)-32;
  if (idx < 0)
    idx = 0;

  while (1) {
    // Ceka na stisk klavesy
    while (1) {
      delay_ms(10);
      if (++cnt == 100) {
        cnt = 0;
        flip_led_d6();
      }
      if ((c = keyboard_idle()) != 0)
        break;
    }
    // Zasifrovani
    if (next(c)) {
      code(hash, encode);
      goto CAESAR;
    }
    // Navrat k predeslemu kroku
    if (back(c))
      return;
    // Posun doleva
    if (c == '*') {
      before_c();
      if (idx > 0) {
      	LCD_send_cmd(LCD_CURSOR_DISPLAY_SHIFT | LCD_SHIFT_DISPLAY | LCD_SHIFT_DIR_RIGHT, 0);
	--idx;
      }
    // Posun doprava
    } else if (c == '#') {
      after_c();
      if (strlen(text) > 32 && strlen(text) > 32 + idx) {
        LCD_rotate();
	++idx;
      }
    // Shift
    } else if (c == 'C') {
      if (text[lcd_cursor_addr] >= 'a' && text[lcd_cursor_addr] <= 'z') {
        text[lcd_cursor_addr] = text[lcd_cursor_addr] - 'a' + 'A';
        LCD_append_char(text[lcd_cursor_addr]);
        before_c();
      } else if (text[lcd_cursor_addr] >= 'A' && text[lcd_cursor_addr] <= 'Z') {
        text[lcd_cursor_addr] = text[lcd_cursor_addr] - 'A' + 'a';
        LCD_append_char(text[lcd_cursor_addr]);
        before_c();
      }
    // Delete
    } else if (c == 'D') {
      i = lcd_cursor_addr;
      if (text[i] == 0 && i > 0)
        --i;
      while (text[i]) {
        text[i] = text[i+1];
        ++i;
      }
      goto CAESAR;
    }
    // Psani
    if (c >= '0' && c <= '9' && idx < 8) {
      if (lcd_cursor_addr >= 32) {
        LCD_rotate();
	++idx;
      }
      text[lcd_cursor_addr] = mobile(text[lcd_cursor_addr], c);
      LCD_append_char(text[lcd_cursor_addr]);
      before_c();
    }
  } 
}

/*******************************************************************************
 * Hlavni funkce
*******************************************************************************/
int main(void)
{
  set_led_d6(1);                       // rozsviceni D6
  char c;
  int encode;
  char number[17] = {0};

  initialize_hardware();
  keyboard_init();
// Napoveda 1. cast
START:
  LCD_clear();
  LCD_append_string("A = Next");
  second_line();
  LCD_append_string("B = Back");

  while (!next(keyboard_idle())) {
    ++cnt;
    if (cnt == 100) {
      cnt = 0;
      flip_led_d6();
    }
    delay_ms(10);
  }
// Napoveda 2. cast
CONFIRM:
  LCD_clear();
  LCD_append_string("C = Shift");
  second_line();
  LCD_append_string("D = Delete");
  while (1) {
    wait(START);
    if (next(c))
      break;
  }
// Napoveda 3. cast
PNCHAR:
  LCD_clear();
  LCD_append_string("* = Prev. char");
  second_line();
  LCD_append_string("# = Next char");
  while (1) {
    wait(CONFIRM);
    if (next(c))
      break;
  }
// Vybirani, jestli bude clovek sifrovat nebo desifrovat
CODE:
  LCD_clear();
  LCD_append_string("1 = Encode");
  second_line();
  LCD_append_string("2 = Decode");
  while (1) {
    wait(PNCHAR);
    if (c == '1') {
      encode = 1;
      break;
    }
    if (c == '2') {
      encode = -1;
      break;
    }
  }
PARAMETER:
  i = strlen(number) - pos;
  LCD_clear();
  LCD_append_string("Zadejte posun:  ");
  LCD_append_string(number);
  while (i >= 0) {
    before();
    --i;
  }
  if (number[pos])
    LCD_append_char(number[pos]);

  while (1) {
    wait(CODE);
    // Zadavani posunu v casarove sifre (jako cislo)
    if ((c != '0' || pos != 0) && c >= '0' && c <= '9' && pos < 16) {
      number[pos] = c;
      LCD_append_char(c);
    // Predchozi cislice
    } else if (c == '*')
      before();
    // Dalsi cislice
    else if (c == '#')
      after();
    // Delete
    else if (c == 'D') {
      i = pos;
      if (!number[i] && i > 0)
        --i;
      while (number[i]) {
        number[i] = number[i+1];
        ++i;
      }
      goto PARAMETER;
    // Prejde k textu k sifrovani
    } else if (next(c) && *number)
      break;
  }
  //Caesarova sifra
  caesar(atoi(number), encode);
  goto PARAMETER;      
}
