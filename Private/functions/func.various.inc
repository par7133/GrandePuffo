<?php

/**
 * Copyright 2021, 2026 5 Mode
 *
 * This file is part of SqueePF.
 *
 * SqueePF is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SqueePF is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.  
 * 
 * You should have received a copy of the GNU General Public License
 * along with SqueePF. If not, see <https://www.gnu.org/licenses/>.
 *
 * func.various.inc
 * 
 * Functions of various kind.
 *
 * @author Daniele Bonini <my25mb@has.im>
 * @copyrights (c) 2016, 2026 5 Mode
 */

/**
 * Replacement for echo with debug checking
 * 
 * @param boolean $debug_var a debug value, if true the echo will be executed 
 * @param list $args a variable argument list
 * @return void
 */
function echo_ifdebug(bool $debug_var, ...$args): void 
{
  if (!DEBUG || !$debug_var) {
    return;
  }
  foreach($args as $arg) {
    echo $arg;
  }
}

function getResource(string $string, string $destLocale = "EN"): string
{
  
  global $LOCALE;
  
  if ($destLocale === "EN") {
    return $string; 
  }    

  if ($LOCALE[$destLocale]["Monday"]==PHP_STR) {
    return $string; 
  }    

  return str_ireplace(array_keys($LOCALE[$destLocale]),array_values($LOCALE[$destLocale]), $string);
}


/**
 * Get an integer result for a division
 * 
 * @param mixed $a first operand
 * @param mixed $b second operand
 * @return int the integer result
 */
function intdiv_1($a, $b): int 
{
  return ($a - $a % $b) / $b;
}

/**
 * Check if the number is odd
 * 
 * @param mixed $a first operand
 * @return bool if the number is odd, true/false
 */
function is_odd($a): bool 
{
  return ($a % 2) > 0;
}

/**
 * Check if the number is pair
 * 
 * @param mixed $a first operand
 * @return bool if the number is pair, true/false
 */
function is_pair($a): bool
{
  return ($a % 2) === 0;
}


/**
 * Check if a variable is set with a default return
 * 
 * @param mixed $var the variable to check
 * @param mixed $default the default value
 * @return mixed the return value
 */
function isset1(&$var, $default=false) 
{
  if (isset($var)) {
    return $var;
  } else {
    return $default;
  }
}

/**
 * Replacement for var_dump with debug checking
 * 
 * @param boolean $debug_var a debug value, if true the var_dump will be executed 
 * @param list $args a variable argument list
 * @return void
 */
function var_dump_ifdebug(bool $debug_var, ...$args): void 
{
  if (!DEBUG || !$debug_var) {
    return;
  }
  foreach($args as $arg) {
    var_dump($arg);
  }
}
