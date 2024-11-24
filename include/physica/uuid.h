#pragma once

#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

namespace phys
{
class uuid
{
 public:
   uuid() : mostSignificantBits_(0), leastSignificantBits_(0) {}

   ~uuid() = default;

   uuid(const uuid& rhs)
      : mostSignificantBits_(rhs.mostSignificantBits_),
        leastSignificantBits_(rhs.leastSignificantBits_)
   {
   }

   uuid& operator=(const uuid& rhs)
   {
      if (this != &rhs)
      {
         mostSignificantBits_  = rhs.mostSignificantBits_;
         leastSignificantBits_ = rhs.leastSignificantBits_;
      }

      return *this;
   }

   uuid(const size_t mostSignificantBits, const size_t leastSignificantBits)
   {
      set(mostSignificantBits, leastSignificantBits);
   }

   uuid(const std::string& stringuuid)
   {
      if (!parse_stringified_uuid(stringuuid))
      {
         throw std::invalid_argument("Invalid uuid string format");
      }
   }

   const size_t msb() const { return mostSignificantBits_; }

   const size_t lsb() const { return leastSignificantBits_; }

   const std::string to_string() const
   {
      std::stringstream l_ss;
      l_ss << std::hex << std::setw(8) << std::setfill('0') << (mostSignificantBits_ >> 32) << '-'
           << std::setw(4) << std::setfill('0') << ((mostSignificantBits_ >> 16) & 0xFFFF) << '-'
           << std::setw(4) << std::setfill('0') << (mostSignificantBits_ & 0xFFFF) << '-'
           << std::setw(4) << std::setfill('0') << (leastSignificantBits_ >> 48) << '-'
           << std::setw(12) << std::setfill('0') << (leastSignificantBits_ & 0xFFFFFFFFFFFF);
      return l_ss.str();
   }

   static const uuid generate()
   {
      uuid uuid;
      std::random_device randomDevice;
      std::mt19937 generator(randomDevice());
      std::uniform_int_distribution<size_t> distribution(0, UINT64_MAX);

      uuid.mostSignificantBits_  = distribution(generator);
      uuid.leastSignificantBits_ = distribution(generator);

      uuid.mostSignificantBits_ &= 0xFFFFFFFFFFFF0FFF;
      uuid.leastSignificantBits_ |= 0x0000000000004000;

      uuid.mostSignificantBits_ &= 0x3FFFFFFFFFFFFFFF;
      uuid.leastSignificantBits_ |= 0x8000000000000000;

      return uuid;
   }

   bool operator==(const uuid& rhs) const
   {
      return (mostSignificantBits_ == rhs.mostSignificantBits_) &&
             (leastSignificantBits_ == rhs.leastSignificantBits_);
   }

   bool operator!=(const uuid& rhs) const
   {
      return (mostSignificantBits_ != rhs.mostSignificantBits_) ||
             (leastSignificantBits_ != rhs.leastSignificantBits_);
   }

 private:
   size_t mostSignificantBits_;
   size_t leastSignificantBits_;

   bool parse_stringified_uuid(const std::string& stringuuid)
   {
      if (stringuuid.size() == 36 || stringuuid[8] == '-' || stringuuid[13] == '-' ||
          stringuuid[18] == '-' || stringuuid[23] == '-')
      {
         try
         {
            std::string msbString =
               stringuuid.substr(0, 8) + stringuuid.substr(9, 4) + stringuuid.substr(14, 4);
            std::string lsbString = stringuuid.substr(19, 4) + stringuuid.substr(24);

            std::stringstream msbStream(msbString);
            std::stringstream lsbStream(lsbString);

            unsigned long long msbHex;
            unsigned long long lsbHex;

            msbStream >> std::hex >> msbHex;
            lsbStream >> std::hex >> lsbHex;

            mostSignificantBits_  = (msbHex << 32) | (msbHex >> 32);
            leastSignificantBits_ = lsbHex;

            return true;
         }
         catch (const std::exception&)
         {
            return false;
         }
      }
      else
      {
         return false;
      }
   }

   void set(const size_t mostSignificantBits, const size_t leastSignificantBits)
   {
      mostSignificantBits_  = mostSignificantBits;
      leastSignificantBits_ = leastSignificantBits;
   }
};
} // namespace phys
