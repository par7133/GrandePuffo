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
 * func.app.inc
 * 
 * App related functions.
 *
 * @author Daniele Bonini <my25mb@has.im>
 * @copyrights (c) 2016, 2026 5 Mode    
 */

use fivemode\fivemode\Config;


/**
 * Retrieve the list of the app hosts 
 * 
 * @return array the hosts array
 */
function getHostsArray(): array {
  $reta = [];
  $reta[] = APP_HOST;
  $i = 2;
  while (true && $i<=10) {
    if (defined("APP_HOST" . $i)) {
      $reta[] = Config::get("APP/HOST" . $i);
    } else {
      break;
    }  
    $i++;
  }
  return $reta;
}


/**
 * 
 * @return string
 */
function getQRCodeUri(string $styleTag): string {
  
  $retval = PHP_STR;
  
  $serverName = strtolower($_SERVER['HTTP_HOST']);
  
  if (mb_stripos1($serverName, "5mode.com") || mb_stripos1($serverName, "localhost")) {
    $retval = "qrcode_5mode" . $styleTag . ".png";
  }
  
  return $retval; 
}


function isSubdomainHost(string &$subdomain) {
  $hostname = str_replace("www.", PHP_STR, strtolower($_SERVER['HTTP_HOST']));    
  $ipos = mb_stripos($hostname, ".");
  $subdomain = left($hostname, $ipos);
  $noSubdomain = false;
  if (($subdomain==="grandepuffo.doggy")) {
    $noSubdomain = true;
  }
  return !$noSubdomain;
}
