/* Bint - A simple big integer library
 * Copyright (C) 2021 Stan Vlad <vstan02@protonmail.com>
 *
 * This file is part of Bint.
 *
 * Bint is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <vector>

#include "Bint.hpp"

#define foreach(index, from, to) \
    for (size_t index = from; index < to; ++index)

Bint::Bint(bool sign, const std::string& value)
: sign(sign && value != "0"), value(value) {}

Bint::Bint(): Bint(false, "0") {}

Bint::Bint(const std::string& str): sign(false), value() {
    std::string target(str);

    if (target[0] == '-') {
        sign = true;
        target.erase(0, 1);
    }

    size_t i = 0;
    while (target[i] == '0') ++i;
    if (i) target.erase(0, i);

    if (target.empty()) {
        value = "0";
        sign = false;
        return;
    }

    value.assign(target.rbegin(), target.rend());
}

Bint::Bint(long long target): sign(false), value() {
    if (target == 0) {
        value = "0";
        return;
    }

    if (target < 0) {
        sign = true;
        target *= -1;
    }

    value.reserve(target <= 9999999999 ? 10 : 20);
    while (target) {
        value += target % 10 + '0';
        target /= 10;
    }
}

size_t Bint::size() const {
    return value.size();
}

Bint Bint::abs() const {
    return Bint { false, value };
}

bool Bint::even() const {
    return (value[0] - '0') % 2 == 0;
}

bool Bint::odd() const {
    return (value[0] - '0') % 2 == 1;
}

bool Bint::prime() const {
    if (*this < 2) return false;
    if (even() && *this != 2) return false;

    for (Bint i = 3; i * i < *this; i += 2) {
        if (*this % i == 0) return false;
    }
    return true;
}

Bint Bint::operator-() const {
    return Bint { !sign, value };
}

Bint Bint::operator+(const Bint& num) const {
    if(*this == 0) return num;
    if(num == 0) return *this;

    Bint sum;
    if (sign == num.sign) {
        sum.value = add(value, num.value);
        sum.sign = sign;
    } else {
        if (value == num.value) return 0;

        bool isLt = lt(value, num.value);
        sum.value = sub(value, num.value, isLt);
        sum.sign = isLt ? num.sign : sign;
    }

    return sum;
}

Bint Bint::operator-(const Bint& num) const {
    return *this + (-num);
}

Bint Bint::operator*(const Bint& num) const {
    if (*this == 0 || num == 0) return 0;

    if (value == "1" || num.value == "1") {
        if (num == 1) return *this;
        if (num == -1) return -*this;
        if (*this == 1) return num;
        if (*this == -1) return -num;
    }

    Bint result {
        sign != num.sign,
        mul(value, num.value[0] - '0', 0)
    };

    foreach(i, 1, num.size()) {
        result.value = add(result.value, mul(value, num.value[i] - '0', i));
    }
    return result;
}

Bint Bint::operator/(const Bint& num) const {
    if (num == 0) {
        throw std::runtime_error("Bint::operator / - Division by zero error");
    }

    if (*this == 0 || lt(value, num.value)) {
        return 0;
    }

    if (num.value == "1") {
        return num.sign ? -*this : *this;
    }

    std::vector<Bint> tab(11);
    foreach(i, 0, 11) tab[i] = num.abs() * i;

    Bint ratio(0), res(false, value.substr(size() - num.size(), num.size()));
    for (ssize_t i = size() - num.size(); i >= 0; --i) {
        ssize_t count = 0;
        while(tab[count] < res) ++count;
        if(tab[count] != res) --count;

        ratio *= 10;
        if(count) ratio += count, res -= tab[count];
        if(i) res = res * 10 + Bint(value[i - 1] - '0');
    }

    if (sign != num.sign) ratio.sign = true;
    return ratio;
}

Bint Bint::operator%(const Bint& num) const {
    if (num == 0) {
        throw std::runtime_error("Bint::operator % - Division by zero error");
    }

    if (*this == 0 || lt(value, num.value)) {
        return *this;
    }

    if (num.value == "1") return 0;

    std::vector<Bint> tab(11);
    foreach(i, 0, 11) tab[i] = num.abs() * i;

    Bint ratio(0), res(false, value.substr(size() - num.size(), num.size()));
    for (ssize_t i = size() - num.size(); i >= 0; --i) {
        ssize_t count = 0;
        while(tab[count] < res) ++count;
        if(tab[count] != res) --count;

        ratio *= 10;
        if(count) ratio += count, res -= tab[count];
        if(i) res = res * 10 + Bint(value[i - 1] - '0');
    }

    if (res != 0) res.sign = sign;
    return res;
}

Bint& Bint::operator++() {
    *this += 1;
    return *this;
}

Bint& Bint::operator--() {
    *this -= 1;
    return *this;
}

Bint Bint::operator++(int) {
    Bint temp(*this);
    *this += 1;
    return temp;
}

Bint Bint::operator--(int) {
    Bint temp(*this);
    *this -= 1;
    return temp;
}

const Bint& Bint::operator+=(const Bint& num) {
    *this = *this + num;
    return *this;
}

const Bint& Bint::operator-=(const Bint& num) {
    *this = *this - num;
    return *this;
}

const Bint& Bint::operator*=(const Bint& num) {
    *this = *this * num;
    return *this;
}

const Bint& Bint::operator/=(const Bint& num) {
    *this = *this / num;
    return *this;
}

const Bint& Bint::operator%=(const Bint& num) {
    *this = *this % num;
    return *this;
}

bool Bint::operator==(const Bint& num) const {
    return sign == num.sign && value == num.value;
}

bool Bint::operator!=(const Bint& num) const {
    return !(*this == num);
}

bool Bint::operator<(const Bint& num) const {
    if (sign > num.sign) return true;
    if (sign < num.sign) return false;
    if (value == num.value) return false;
    return sign == !lt(value, num.value);
}

bool Bint::operator<=(const Bint& num) const {
    return *this == num || *this < num;
}

bool Bint::operator>(const Bint& num) const {
    return !(*this <= num);
}

bool Bint::operator>=(const Bint& num) const {
    return !(*this < num);
}

std::ostream& operator<<(std::ostream& os, const Bint& num) {
    if (num.sign) {
        os << '-';
    }

    std::string target;
    target.assign(num.value.rbegin(), num.value.rend());
    os << target;

    return os;
}

std::istream& operator>>(std::istream& is, Bint& num) {
    std::string target;
    is >> target;
    num = Bint(target);
    return is;
}

bool Bint::lt(const std::string& str1, const std::string& str2) const {
    if (str1.size() < str2.size()) return true;
    if (str1.size() > str2.size()) return false;

    for (ssize_t i = str1.size() - 1; i >= 0; --i) {
        if(str1[i] < str2[i]) return true;
        if(str1[i] > str2[i]) return false;
    }
    return false;
}

std::string Bint::add(const std::string& str1, const std::string& str2) const {
    const std::string& min = str1.size() < str2.size() ? str1 : str2;
    const std::string& max = str1.size() < str2.size() ? str2 : str1;

    size_t minSize = min.size();
    size_t maxSize = max.size();

    std::string result;
    result.reserve(maxSize + 1);

    int c = 0;
    foreach(i, 0, minSize) {
        int s = c + max[i] + min[i] - 2 * '0';
        c = s / 10;
        result += '0' + s % 10;
    }

    foreach(i, minSize, maxSize) {
        int s = c + max[i] - '0';
        c = s / 10;
        result += '0' + s % 10;
    }

    if (c) result += '0' + c;
    return result;
}

std::string Bint::sub(const std::string& str1, const std::string& str2, bool lt) const {
    const std::string& min = lt ? str1 : str2;
    const std::string& max = lt ? str2 : str1;

    size_t minSize = min.size();
    size_t maxSize = max.size();

    std::string result;
    result.reserve(maxSize);

    int c = 0;
    foreach(i, 0, minSize) {
        int s = c + max[i] - min[i];
        if (s >= 0) c = 0;
        else c = -1, s += 10;
        result += s + '0';
    }

    foreach(i, minSize, maxSize) {
        int s = c + max[i] - '0';
        if (s >= 0) c = 0;
        else c = -1, s += 10;
        result += s + '0';
    }

    size_t i = 0, size = result.size();
    while (result[size - i - 1] == '0') ++i;
    if (i) result.erase(size - i, i);

    return result;
}

std::string Bint::mul(const std::string& str1, int digit, size_t pos) const {
    size_t size = str1.size();

    std::string result;
    result.reserve(size + pos + 1);

    while (pos--) result += '0';

    int c = 0;
    foreach(i, 0, size) {
        int s = c + digit * (str1[i] - '0');
        c = s / 10;
        result += '0' + s % 10;
    }

    if (c) result += '0' + c;
    return result;
}
