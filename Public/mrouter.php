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
 * mrouter.php
 * 
 * The main router.
 *
 * @author Daniele Bonini <my25mb@has.im>
 * @copyrights (c) 2016, 2026 5 Mode     
 */

require "../Private/core/init.inc";


// FUNCTION AND VARIABLE DECLARATIONS


// PARAMETERS VALIDATION

$url = filter_input(INPUT_GET, "url")??"";
$url = strip_tags($url);
$url = strtolower(trim(substr($url, 0, 300), "/"));

$rndPrefix = substr($url, 0, 6);

$myResRouter = getResRouter($rndPrefix);

if ($myResRouter !== PHP_STR) {

    $scriptPath = APP_ROUTE_PATH;
    define("ROUTE_NAME", "router");
    define("ROUTE_FILENAME", $myResRouter );  
  
    header("Content-Type: image/png");
        
    require(APP_PUBLIC_PATH . "/$myResRouter");
    
} else {
    $scriptPath = APP_ERROR_PATH;
    define("ROUTE_NAME", "err-404");
    define("ROUTE_FILENAME", "err-404.php");  
    
    if (ROUTE_NAME==="err-404") {
      header("HTTP/1.1 404 Not Found");
    }  
          
    require $scriptPath . "/" . ROUTE_FILENAME;
}
