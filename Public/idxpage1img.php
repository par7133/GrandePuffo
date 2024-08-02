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

use fivemode\fivemode\Cookie;
use fivemode\fivemode\Puffi;


// FUNCTION AND VARIABLE DECLARATIONS

// Cookie reset..
function resetCookies() {
    Cookie::set($mySha, "0", Cookie::EXPIRE_ONEDAY, "/", APP_HOST);
    Cookie::set($mySha."0", "", Cookie::EXPIRE_ONEDAY, "/", APP_HOST);
    Cookie::set($mySha."1", "", Cookie::EXPIRE_ONEDAY, "/", APP_HOST);
    Cookie::set($mySha."2", "", Cookie::EXPIRE_ONEDAY, "/", APP_HOST);
    Cookie::set($mySha."3", "", Cookie::EXPIRE_ONEDAY, "/", APP_HOST);
    Cookie::set($mySha."4", "", Cookie::EXPIRE_ONEDAY, "/", APP_HOST);
}

// Increment image instance counter..
function setCookieCounter() {

    // set iteraction counter..    

   global $ROUTING;
   global $myShaCounter;
   global $mySha;

   while(true) {
      $myShaCounter++;    

      if (!defined("ROUTING_RES".$myShaCounter)) {
         Cookie::set($mySha, 0, Cookie::EXPIRE_ONEDAY, "/", APP_HOST);  
         break;
      }  
                                                         
      if ($ROUTING['RES_TYPE'][$myShaCounter]==="image") {
          Cookie::set($mySha, $myShaCounter, Cookie::EXPIRE_ONEDAY, "/", APP_HOST);
          break;
      }
  }
}

$myTmpResPath = "";


// PARAMETERS VALIDATION


//$myDisplaiedSha = substr($url,7,strlen($url)-11);
$myDisplaiedSha = substr($url,7,strlen($url));

$myResIdx=getRes($myDisplaiedSha);
// echo("**".$myResIdx."**");
$mySha = $ROUTING['RES_SHA'][$myResIdx]; 

$myShaCounter = Cookie::get($mySha, 0);
//echo("**".$myShaCounter."**");
 
$myResType = $ROUTING['RES_TYPE'][$myShaCounter];
// echo("**".$myResType."**");
  
if ($myResType==="image") {

      //$mySha = $ROUTING['RES_SHA'][$myResIdx];
      $myPageElementID = $ROUTING['WEBPAGE_ELEMENT'][$myShaCounter];
      $myRes = Puffi::getres($mySha,$myShaCounter); 
      //echo("--".$myRes."--");
      $cookiePath = Cookie::get($mySha.$myShaCounter, PHP_STR);

      if ( $cookiePath !== $cookiePath) {

        $myTmpResPath = $cookiePath;
        $myTmpResRelPath = substr($myTmpResPath, strlen(APP_PUBLIC_PATH));

      } else { 

        $myTmpResRoot = APP_PUBLIC_PATH . DIRECTORY_SEPARATOR . "tmpres";

        $myTmpResPath = getNewTmpFileName($myTmpResRoot, pathinfo($myRes, PATHINFO_EXTENSION));
        $myTmpResRelPath = substr($myTmpResPath, strlen(APP_PUBLIC_PATH));
        
        genTmpRes(APP_PUBLIC_PATH . DIRECTORY_SEPARATOR . $myRes, $myTmpResPath);

        Cookie::set($mySha.$myShaCounter, $myTmpResPath, Cookie::EXPIRE_ONEDAY, "/", APP_HOST);

      }

}

if (is_readable($myTmpResPath)) {
    $filecont = file_get_contents($myTmpResPath);
    echo($filecont);
}

setCookieCounter();
