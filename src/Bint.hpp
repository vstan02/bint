/* Bint - A simple big integer library
 * Copyright (C) 2021-2022 Stan Vlad <vstan02@protonmail.com>
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

#ifndef BIG_INT_HPP
#define BIG_INT_HPP

#include <string>
#include <iostream>

class Bint {
    public:
        Bint();
        Bint(long long);
        explicit Bint(const std::string&);

        [[nodiscard]] size_t size() const;
        [[nodiscard]] Bint abs() const;

        [[nodiscard]] bool prime() const;
        [[nodiscard]] bool odd() const;
        [[nodiscard]] bool even() const;

        Bint& operator=(const Bint&) = default;

        Bint operator-() const;
        Bint operator+(const Bint&) const;
        Bint operator-(const Bint&) const;
        Bint operator*(const Bint&) const;
        Bint operator/(const Bint&) const;
        Bint operator%(const Bint&) const;

        Bint& operator++();
        Bint& operator--();
        Bint operator++(int);
        Bint operator--(int);

        const Bint& operator+=(const Bint&);
        const Bint& operator-=(const Bint&);
        const Bint& operator*=(const Bint&);
        const Bint& operator/=(const Bint&);
        const Bint& operator%=(const Bint&);

        bool operator==(const Bint&) const;
        bool operator!=(const Bint&) const;
        bool operator<(const Bint&) const;
        bool operator<=(const Bint&) const;
        bool operator>(const Bint&) const;
        bool operator>=(const Bint&) const;

        friend std::ostream& operator<<(std::ostream&, const Bint&);
        friend std::istream& operator>>(std::istream&, Bint&);

    private:
        bool sign;
        std::string value;

    private:
        Bint(bool, const std::string&);

        [[nodiscard]] bool lt(const std::string&, const std::string&) const;
        [[nodiscard]] std::string add(const std::string&, const std::string&) const;
        [[nodiscard]] std::string sub(const std::string&, const std::string&, bool) const;
        [[nodiscard]] std::string mul(const std::string&, int, size_t) const;
};

#endif // BIG_INT_HPP
