<?php

/**
 * Copyright 2021, 2026 5 Mode
 *
 * This file is part of GrandePuffo.
 *
 * GrandePuffo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GrandePuffo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.  
 * 
 * You should have received a copy of the GNU General Public License
 * along with GrandePuffo. If not, see <https://www.gnu.org/licenses/>.
 *
 * class.puffi.inc
 * 
 * Puffi class.
 *
 * @author Daniele Bonini <my25mb@has.im>
 * @copyrights (c) 2016, 2026, 5 Mode
 **/

namespace fivemode\fivemode;

/**
 * Puffi
 *
 * Puffi class
 *
 * @package  Puffi
 * @author   Daniele Bonini <my25mb@has.im>
 * @version  1.0
 * @access   public
 */
final class Puffi {
  
  static private $counter = -1;
  
  /**
   * Default constructor
   * 
   * @return void
   */
  private function __construct()
  {
  }

  static public function getcounter(): int
  {
    return self::$counter+1;
  }
      
  /**
   * Check if the given cookie exists
   *
   * @param string $name the name of the cookie
   * @return bool if the given cookie exist, true/false
   */
  static public function getres(string $sha, int $mycounter): string
  {
    //self::$counter++;
    return constant("ROUTING_RES" . $mycounter);
  }
}
