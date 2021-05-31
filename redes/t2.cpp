#include <cstdlib> // Rand
#include <ctime> //Time
#include <iostream> // Input/Output
#include <string> // String
#include <sstream> // StrinStream
#include <vector> // Vector, vector<bool>
#include <bitset> // Bitset

/* Uncoment this line if you want a verbose
 * function-by-function print of what's
 * happening.
 */
#define DEBUG true

// Error checking namespace
namespace EvenChecker {
  bool _get_is_even (std::vector<bool>& bits) {
    bool is_even = false;
    for (auto bit : bits)
      if (bit) is_even = !is_even;
    return is_even;
  }

  void encode (std::vector<bool>& bits) {
    bits.push_back(_get_is_even(bits));
  }

  bool decode (std::vector<bool>& bits) {
    return _get_is_even(bits);
  }
}

namespace OddChecker {
  bool _get_is_odd (std::vector<bool>& bits) {
    bool is_even = false;
    for (auto bit : bits)
      if (bit) is_even = !is_even;
    return !is_even;
  }

  void encode (std::vector<bool>& bits) {
    bits.push_back(_get_is_odd(bits));
  }

  bool decode (std::vector<bool> bits) {
    return _get_is_odd(bits);
  }
}

namespace CRC32Checker {
  const int CRC_POLY = 0x04C11DB7; //CRC generator polynomial.

  //The CRC computation could be improved;
  //For learning reasons, I'll leave it this way.   
  int32_t _compute_crc_32(std::vector<bool> bits)
  {
    int32_t crc = 0x0; //32bit variable
    std::vector<uint8_t> result;
    int count = 0;
    uint8_t temp = 0;

    //printf("Bit len: %lu\n", bits.size());
    for (auto bit : bits)
    {
      //printf("Temp is: 0x%x\n", temp);
      ////Generate int vector.
      //printf("Bit is: %x\n", (bool)bit);
      temp |= (bool)bit;
      if (++count > 7)
      {
        //printf("Pushing back 0x%x\n", temp);
        result.push_back(temp);
        temp = 0;
        count = 0;
      }
      temp <<= 1;
    }

    for (uint8_t& byte : result)
    {
      //std::cout << "Processing " << byte << std::endl;
      crc ^= (int32_t) (byte << 24); //Cast to 32 bit

      for (int i = 0; i < 8; i++)
      {
          if ((crc & 0x80000000) != 0) //If MSB is set. 
          {
              crc = (uint)((crc << 1) ^ CRC_POLY);
          }
          else
          {
              crc <<= 1;
          }
      }
    }

    return crc;
  }

  void encode(std::vector<bool>& bits)
  {
    int32_t crc = _compute_crc_32(bits);
    #ifdef DEBUG
    printf("Encode: CRC hex: 0x%x\n", crc);
    #endif

    for (int i = 0 ; i < 32 ; i++)
    {
      if (crc & 0x80000000)
      {
        bits.push_back(true);
      }
      else
      {
        bits.push_back(false);
      }
      crc <<= 1;
    }
  }

  bool decode(std::vector<bool>& bits)
  {
    int32_t crc = _compute_crc_32(bits);
    #ifdef DEBUG
    printf("Decoded: CRC hex: 0x%x\n", crc);
    #endif

    if (crc != 0) return true; //Error is true
    return false;
  }
}

/// Converte uma string para um bitset dos códigos ASCII
/// De cada Caracetere
std::vector<bool> str_bit_conv(std::string& s) {
  std::vector<bool> bits;
  for (const char& c : s) {
    std::bitset<8u> byte(c);
    for (size_t i = 0; i < 8; i++)
      bits.push_back(byte[i]);
  }
  return bits;
}

/// Converte um bitset de códigos ASCII para uma string
std::string str_bit_conv(std::vector<bool>& bits) {
  size_t i = 1;
  unsigned byte = 0;
  std::stringstream ss;
  for (auto bit : bits) {
    if (bit) byte += i;
    i *= 2;
    if (i == 256) {
      ss << (char) byte;
      byte = 0, i = 1;
    }
  }
  return ss.str();
}

// These definitions are only for better reading of
// follwing code.
void out_app (void);
void out_app_layer (std::string msg);
void out_lace_layer (std::vector<bool> bits);
void com_mean (std::vector<bool> bit_stream);
void in_lace_layer (std::vector<bool> bits);
void in_app_layer (std::vector<bool> bits);
void in_app (std::string msg);

/*
 * #################################################
 * Aplication. These next lines are made so you can
 * follow the flow like a book
 * #################################################
 * */
int main (void) {
  out_app();
  return 0;
}

// Transmiting application
void out_app (void) {
  std::string message;
  std::cout << "Digite uma mensagem: ";
  std::cin >> message;
  out_app_layer(message);
}

// Transmiting application layer
void out_app_layer (std::string msg) {
  std::vector<bool> bits = str_bit_conv(msg);

  #ifdef DEBUG
  std::cout << "Bits generated from message:\n";
  for (auto bit : bits)
    std::cout << bit;
  std::cout << '\n';
  #endif

  out_lace_layer(bits);
}

// Transmiting application lace layer
void out_lace_layer (std::vector<bool> bits) {
  // TODO error control
  //OddChecker::encode(bits);
  CRC32Checker::encode(bits);

  #ifdef DEBUG
  std::cout << "After encoding for error checking\n";
  for (auto bit : bits)
    std::cout << bit;
  std::cout << '\n';
  #endif

  com_mean(bits);
}

// Comunication mean, passing data through
void com_mean (std::vector<bool> bit_stream) {
  unsigned error_rate = 2; // In percentage
  //unsigned error_rate = 0; // In percentage

  //Seed the randomness prevent from always giving same result
  std::srand(time(NULL));

  for (auto bit : bit_stream)
    if (std::rand() % 100 < error_rate)
      bit = !bit;
  in_lace_layer(bit_stream);
}

// Receiving application lace layer
void in_lace_layer (std::vector<bool> bits) {
  #ifdef DEBUG
  std::cout << "After going through comunication mean\n";
  for (auto bit : bits)
    std::cout << bit;
  std::cout << '\n';
  #endif

  // TODO error checking

  //if (OddChecker::decode(bits))
  if (CRC32Checker::decode(bits))
    std::cout << "[WAR] There was an error detected in your message. "
      "Message may appear weird.\n";

  //TODO: Simplify and generalize this.
  //Remove 32 trailing bits.
  std::vector<bool> stripped_bits;
  uint32_t c = 0;
  for (auto bit : bits)
  {
    if (c++ >= bits.size() - 32) break;
    stripped_bits.push_back(bit);
  }

  in_app_layer(stripped_bits);
}

// Receiving application layer
void in_app_layer (std::vector<bool> bits) {
  std::string message = str_bit_conv(bits);
  in_app(message);
}

// Receiving application
void in_app (std::string msg) {
  std::cout << "A mensagem recebida foi: '" << msg << "'\n";
  // END
}
