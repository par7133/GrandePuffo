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
 * func.string.inc
 * 
 * String related functions.
 *
 * @author Daniele Bonini <my25mb@has.im>
 * @copyrights (c) 2016, 2026 5 Mode
 */


function genTmpRes(string $myRes, string $myTmpResPath): void
{
  cp($myRes,$myTmpResPath);
  if (is_readable($myTmpResPath)) {
    chmod($myTmpResPath, 0655);  
  }  
}


function getRes(string $displaiedSha): int
{
    global $ROUTING;

    //echo("displaiedSha=$displaiedSha");
    $tot = count($ROUTING['RES_PASSWORD'])-1;
    $i=0;
    while ($i<=$tot) {
      //echo("#$i=".hash("sha256", $ROUTING['RES_PASSWORD'][$i] . $ROUTING['RES_SALT'][$i])."<br>");
      if (hash("sha256", $ROUTING['RES_PASSWORD'][$i] . $ROUTING['RES_SALT'][$i]) === $displaiedSha) {
        return $i; 
      }
      $i++;
    } 
}


function getResIndex(string $myPrefix):  string
{
    global $ROUTING;
 
    $i=0;
    foreach($ROUTING['RES_ROUTER_PREFIX'] as $prefix) {
      if ($prefix[0]>=$myPrefix && $myPrefix<=$prefix[1]) {
        return $i;
      }
      $i++;
    }
}
      
                  
function getResRouter(string $myPrefix):  string
{
    global $ROUTING;
 
    $i=0;
    foreach($ROUTING['RES_ROUTER_PREFIX'] as $prefix) {
      if ($prefix[0]>=$myPrefix && $myPrefix<=$prefix[1]) {
        return $ROUTING['RES_ROUTER'][$i];
      }
      $i++;
    }
}
