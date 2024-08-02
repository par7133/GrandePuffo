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
 * func-filter.inc
 * 
 * Custom filtering functions.
 *
 * @author Daniele Bonini <my25mb@has.im>
 * @copyrights (c) 2016, 2026 5 Mode
 */

use fivemode\fivemode\Err;
use fivemode\fivemode\ErrUtil;


// Validate / sanitize a given string
define("FILTER_SANITIZE_BOOLEAN", 1);
define("FILTER_SANITIZE_ERRMSG", 2);
define("FILTER_SANITIZE_FILENAME", 3);
define("FILTER_SANITIZE_FILENAME_WITH_SPACE", 4);
define("FILTER_SANITIZE_FILEPATH", 5);
define("FILTER_SANITIZE_IMAGENAME", 6);
define("FILTER_SANITIZE_LANGUAGE", 7);
define("FILTER_SANITIZE_KEY", 8);
define("FILTER_SANITIZE_MD5TOKEN", 9);
define("FILTER_SANITIZE_Q", 10);
define("FILTER_SANITIZE_QM", 11);
define("FILTER_SANITIZE_SCRIPTNAME", 12);
define("FILTER_SANITIZE_SHA2TOKEN", 13);
define("FILTER_SANITIZE_STRING_WITHBR", 14);
define("FILTER_SANITIZE_TAG", 15);
define("FILTER_SANITIZE_TAGS", 16);
define("FILTER_SANITIZE_URL1", 17);
define("FILTER_SANITIZE_USERNAME", 18);
define("FILTER_SANITIZE_FILEPATH_LESS", 19);
define("FILTER_CLEAN_LANDINGPAGE", 100);
define("FILTER_VALIDATE_ERRNO", 200);
define("FILTER_VALIDATE_IMAGENAME", 201);
define("FILTER_VALIDATE_LANGUAGE", 202);
define("FILTER_VALIDATE_SHA2TOKEN", 203);
define("FILTER_VALIDATE_MD5TOKEN", 204);
define("FILTER_VALIDATE_REFID", 205);
define("FILTER_VALIDATE_USERNAME", 206);
define("FILTER_VALIDATE_TIMEWINDOW", 207);


/**
 * Sanitize a given variable
 * 
 * @param string $string the string to check
 * @param integer $filter the type of filter to apply
 * @param mixed $param (optional) for various purpose
 * @return mixed the string filtered, a boolean if the string is validate
 */
function filter_var1(string $string, int $filter, $param = null) {
  if ($string=="") {
    return $string;
  }  
  switch ($filter) {
    case FILTER_SANITIZE_BOOLEAN:
      return preg_replace("/[^0-1]/iu", "", $string);
    case FILTER_SANITIZE_ERRMSG:
      return str_replace(chr(10)," ", str_replace(chr(13)," ",filter_var($string, FILTER_SANITIZE_STRING, FILTER_FLAG_ENCODE_HIGH | FILTER_FLAG_STRIP_BACKTICK)));
    case FILTER_SANITIZE_FILENAME:
      return preg_replace("/[^\w\-.]/iu", "", $string);
    case FILTER_SANITIZE_FILENAME_WITH_SPACE:
      return preg_replace("/[^\w\-. ]/iu", "", $string);
    case FILTER_SANITIZE_FILEPATH:
      return preg_replace("/[^A-Za-z0-9-_.\/]/", "", $string);
    case FILTER_SANITIZE_IMAGENAME:
      return str_replace("_", "", preg_replace("/[^\w\- ]/iu", "", $string));
    case FILTER_SANITIZE_KEY:
      return preg_replace("/[^A-Za-z0-9-_]/", "", $string);
    case FILTER_SANITIZE_LANGUAGE:
      return preg_replace("/[^A-Za-z\-]/", "", $string);      
    case FILTER_SANITIZE_MD5TOKEN:
      return preg_replace("/[^A-Za-z0-9]/", "", $string);
    case FILTER_SANITIZE_Q:
      return trim(preg_replace("/[^\w\-: ]/iu", "", $string));
    case FILTER_SANITIZE_QM:
      return trim(preg_replace("/[^\w\.\-: ]/iu", "", $string));      
    case FILTER_SANITIZE_SCRIPTNAME:
      return preg_replace("/[^A-Za-z0-9-_]/", "", $string);
    case FILTER_SANITIZE_SHA2TOKEN:
      return preg_replace("/[^A-Za-z0-9]/", "", $string);
    case FILTER_SANITIZE_STRING_WITHBR:
      return str_replace("&NewLine;", "<br>", filter_var(str_replace("<br>", "&NewLine;", isset1($string,"")), FILTER_SANITIZE_STRING));
    case FILTER_SANITIZE_TAG:
      return preg_replace("/[^\w\-]/iu", "", $string);
    case FILTER_SANITIZE_TAGS:
      return preg_replace("/[^\w\- ]/iu", "", $string);
    case FILTER_SANITIZE_URL1:
      return preg_replace("/[^\w\-]/iu", "", $string);
    case FILTER_SANITIZE_USERNAME:
      return preg_replace("/[^\w\-]/", "", $string);
    case FILTER_SANITIZE_FILEPATH_LESS:
      $s = $string;
      $s = str_replace("../", PHP_STR, $s);
      $s = str_replace("..", PHP_STR, $s);
      $s = str_replace("/", PHP_STR, $s);
      $s = str_replace("*", PHP_STR, $s);
      $s = str_replace("?", PHP_STR, $s);
      $s = str_replace("%", PHP_STR, $s);
      return trim_word($s, ['../', '..', '/', '*', '?', '%', '.']);
    case FILTER_CLEAN_LANDINGPAGE:
      $posLandingPage = strpos($string, "lndp");
      $i = strpos($string, "&");
      if ($posLandingPage===false) {
        return $string;
      }  
      if ($i===false) {
        return "";
      } else {
        return substr($string, $i+1); 
      }
      break;
    case FILTER_VALIDATE_ERRNO:
      if (preg_match("/^[0-9]+?$/", $string)) {
        return true;
      } else {
        if (preg_match("/^([a-zA-Z0-9]{32})?$/", $string) && ErrUtil::isValidError($string)) {
          return true;
        } else {
          return false;
        }
      }
    case FILTER_VALIDATE_IMAGENAME:
      return (mb_strlen($string)>=3 && mb_strlen($string)<=50 && preg_match("/^[\w\- ]+?$/iu", $string) && !stripos($string,"_"));
    case FILTER_VALIDATE_LANGUAGE:
      return preg_match("/^([a-z]{2}\-[A-Z]{2})?$/", $string);
    case FILTER_VALIDATE_REFID:
      if (!filter_var($string, FILTER_VALIDATE_INT)) {
        return false;
      } 
      if (hash("sha256", $string . APP_SALT, false) != $param) {
        return false;
      }
      return true;
    case FILTER_VALIDATE_SHA2TOKEN:
      return preg_match("/^([a-zA-Z0-9]{64})?$/", $string);
    case FILTER_VALIDATE_MD5TOKEN:
      return preg_match("/^([a-zA-Z0-9]{32})?$/", $string);      
    case FILTER_VALIDATE_USERNAME:
      return (strlen($string)>=3 && strlen($string)<=20 && preg_match("/^[\w\-]+?$/", $string));
    case FILTER_VALIDATE_TIMEWINDOW:
      return (strlen($string)===2 && preg_match("/^[0-9][d|w]$/", $string));
    default:
      Err::trigger_error1(ERR::ERR_GENERAL, "filter_var1: $filter filter: not implemented", __FILE__, __LINE__);
      break;
  }
}  

//INPUT_POST
//INPUT_GET
//INPUT_COOKIE
//INPUT_ENV
//INPUT_SERVER
//INPUT_SESSION
//INPUT_REQUEST

/**
 * Sanitize a given input string
 * 
 * @param integer $inputType the type of input INPUT_POST, INPUT_GET, etc.
 * @param string $key the key of the input
 * @param integer $filter the type of filter to apply
 * @param mixed $param (optional) for various purpose
 * @return mixed the string filtered, a boolean if the string is validate
 */
function filter_input1(int $inputType, string $key, int $filter, $param = null) {
  
  $input = array();  
  switch ($inputType) {
    case INPUT_POST:
      $input =& $_POST;
      break;
    case INPUT_GET:
      $input =& $_GET;
      break;
    default:
      Err::trigger_error1(ERR::ERR_GENERAL, "filter_input1: $inputType inputType: not implemented", __FILE__, __LINE__);
      break;
  }
  
  if (!isset($input[$key])) {
    return null;
  }
  
  switch ($filter) {
    case FILTER_SANITIZE_BOOLEAN:
      return preg_replace("/[^0-1]/iu", "", $input[$key]);
    case FILTER_SANITIZE_ERRMSG:
      return str_replace(chr(10)," ", str_replace(chr(13)," ",filter_var($input[$key], FILTER_SANITIZE_STRING, FILTER_FLAG_ENCODE_HIGH | FILTER_FLAG_STRIP_BACKTICK)));
    case FILTER_SANITIZE_Q:
      return trim(preg_replace("/[^\w\-: ]/iu", "", $input[$key]));
    case FILTER_SANITIZE_QM:
      return trim(preg_replace("/[^\w\.\-: ]/iu", "", $input[$key]));  
    case FILTER_SANITIZE_MD5TOKEN:
      return preg_replace("/[^A-Za-z0-9]/", "", $input[$key]);
    case FILTER_SANITIZE_FILENAME:
      return preg_replace("/[^\w\-.]/iu", "", $input[$key]);
    case FILTER_SANITIZE_FILENAME_WITH_SPACE:
      return preg_replace("/[^\w\-. ]/iu", "", $input[$key]);
    case FILTER_SANITIZE_FILEPATH:
      return preg_replace("/[^A-Za-z0-9-_.\/]/", "", $input[$key]);
    case FILTER_SANITIZE_IMAGENAME:
      return str_replace("_", "", preg_replace("/[^\w\- ]/iu", "", $input[$key]));      
    case FILTER_SANITIZE_KEY:
      return preg_replace("/[^A-Za-z0-9-_]/", "", $input[$key]);
    case FILTER_SANITIZE_LANGUAGE:
      return preg_replace("/[^A-Za-z\-]/", "", $input[$key]);      
    case FILTER_SANITIZE_SCRIPTNAME:
      return preg_replace("/[^A-Za-z0-9-_]/", "", $input[$key]);
    case FILTER_SANITIZE_SHA2TOKEN:
      return preg_replace("/[^A-Za-z0-9]/", "", $input[$key]);
    case FILTER_SANITIZE_STRING_WITHBR:
      return str_replace("&NewLine;", "<br>", filter_var(str_replace("<br>", "&NewLine;", isset1($input[$key],"")), FILTER_SANITIZE_STRING));
    case FILTER_SANITIZE_TAG:
      return preg_replace("/[^\w\-]/iu", "", $input[$key]);
    case FILTER_SANITIZE_TAGS:
      return preg_replace("/[^\w\- ]/iu", "", $input[$key]);
    case FILTER_SANITIZE_URL1:
      return preg_replace("/[^\w\-]/iu", "", $input[$key]);
    case FILTER_SANITIZE_USERNAME:
      return preg_replace("/[^\w\-]/", "", $input[$key]);
    case FILTER_SANITIZE_FILEPATH_LESS:
      $s = $input[$key];
      $s = str_replace("../", PHP_STR, $s);
      $s = str_replace("..", PHP_STR, $s);
      $s = str_replace("/", PHP_STR, $s);
      $s = str_replace("*", PHP_STR, $s);
      $s = str_replace("?", PHP_STR, $s);
      $s = str_replace("%", PHP_STR, $s);
      return trim_word($s, ['../', '..', '/', '*', '?', '%', '.']);
    case FILTER_CLEAN_LANDINGPAGE:
      $posLandingPage = strpos($input[$key], "lndp");
      $i = strpos($input[$key], "&");
      if ($posLandingPage===false) {
        return $input[$key];
      }  
      if ($i===false) {
        return "";
      } else {
        return substr($input[$key], $i+1); 
      }
      break;
    case FILTER_VALIDATE_ERRNO:
      if (preg_match("/^[0-9]+?$/", $input[$key])) {
        return true;
      } else {
        if (preg_match("/^([a-zA-Z0-9]{32})?$/", $input[$key]) && ErrUtil::isValidError($string)) {
          return true;
        } else {
          return false;
        }
      }
    case FILTER_VALIDATE_IMAGENAME:
      return (mb_strlen($input[$key])>=3 && mb_strlen($input[$key])<=50 && preg_match("/^[\w\- ]+?$/iu", $input[$key]) && !stripos($input[$key], "_"));
    case FILTER_VALIDATE_LANGUAGE:
      return preg_match("/^([a-z]{2}\-[A-Z]{2})?$/", $input[$key]);
    case FILTER_VALIDATE_REFID:
      if (!filter_var($input[$key], FILTER_VALIDATE_INT)) {
        return false;
      } 
      if (hash("sha256", $input[$key] . APP_SALT, false) != $param) {
        return false;
      }
      return true;
    case FILTER_VALIDATE_SHA2TOKEN:
      return preg_match("/^([a-zA-Z0-9]{64})?$/", $input[$key]);
    case FILTER_VALIDATE_MD5TOKEN:
      return preg_match("/^([a-zA-Z0-9]{32})?$/", $input[$key]);  
    case FILTER_VALIDATE_USERNAME:
      return (strlen($input[$key])>=3 && strlen($input[$key])<=20 && preg_match("/^[\w\-]+?$/", $input[$key]));
    case FILTER_VALIDATE_TIMEWINDOW:
      return (strlen($input[$key])===2 && preg_match("/^[0-9][d|w]$/", $input[$key]));
    default:
      Err::trigger_error1(ERR::ERR_GENERAL, "filter_var1: $filter filter: not implemented", __FILE__, __LINE__);
      break;
  }
}

?>
