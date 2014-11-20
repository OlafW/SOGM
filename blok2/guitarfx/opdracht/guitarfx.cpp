/**********************************************************************
*          Copyright (c) 2013, Hogeschool voor de Kunsten Utrecht
*                      Hilversum, the Netherlands
*                          All rights reserved
***********************************************************************
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.
*  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************
*
*  File name     : guitarfx.cpp
*  System name   : guitarfx
* 
*  Description   : main file for guitarfx
*
*  Author        : Marc_G
*  E-mail        : marcg@dinkum.nl
*
**********************************************************************/

#include <iostream>

#define BUFFERSIZE 10

using namespace std;


class Amplifier
{
public:
  Amplifier(); // constructor
  void show_level();
private:
  long level;
};

Amplifier::Amplifier()
{
  this->level=5; // default
}


void Amplifier::show_level()
{
  cout << "Amplifier level: " << level << endl;
}


int main()
{
Amplifier amp;

  amp.show_level();

} // main()

