<?php

/**
 * Copyright (c) 2016, 2024, 5 Mode
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither 5 Mode nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software 
 *       without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * class.cookie.inc
 * 
 * Cookie class.
 *
 * @author Daniele Bonini <my25mb@aol.com>
 * @copyrights (c) 2016, 2024, 5 Mode 
 * @license https://opensource.org/licenses/BSD-3-Clause 
 */

namespace fivemode\fivemode;

/**
 * Cookie
 *
 * Cookie class
 *
 * @package  Cookie
 * @author   Daniele Bonini <my25mb@aol.com>
 * @version  2.0
 * @access   public
 */
final class Cookie {
  
  const EXPIRE_ONEDAY = 86400;
  const EXPIRE_SEVENDAYS = 604800;
  const EXPIRE_THIRTYDAYS = 2592000;
  const EXPIRE_SIXMONTHS = 15768000;
  const EXPIRE_ONEYEAR = 31536000;
  const EXPIRE_LIFETIME = -1;

  /**
   * Default constructor
   * 
   * @return void
   */
  private function __construct()
  {
  }
  
  /**
   * Check if the given cookie exists
   *
   * @param string $name the name of the cookie
   * @return bool if the given cookie exist, true/false
   */
  static public function exists(string $name): bool
  {
    return isset($_COOKIE[COOKIE_PREFIX . $name]);
  }

  /**
   * Check if the given cookie is empty
   *
   * @param string $name the name of the cookie
   * @return bool if the given cookie is empty, true/false
   */
  static public function isEmpty(string $name): bool
  {
    if (!self::exists($name)) {
      return true;
    }
    return empty($_COOKIE[COOKIE_PREFIX . $name]);
  }

  /**
   * Get the value of the given cookie
   *
   * @param string $name the name of the cookie
   * @param string $default the default value
   * @return string the value of the cookie
   */
  static public function get(string $name, string $default = ""): string
  {
    return (self::exists($name) ? $_COOKIE[COOKIE_PREFIX . $name] : $default);
  }

  /**
   * Set the value of a given cookie
   * 
   * @param string $name the name of the cookie
   * @param string $value the value
   * @param mixed $expire the expiration time
   * @param string $path the path
   * @param mixed $domain the domain
   * @return bool if the cookie has been successfully set, true/false
   */
  static public function set(string $name, string $value, ?int $expire = self::EXPIRE_ONEYEAR, string $path = "/", $domain = false): bool
  {
    $retval = false;
    
    settype($subdomain, "string");
    
    if (!headers_sent())
    {
      if ($domain === false) {
        //$domain = $_SERVER['HTTP_HOST'];
        $domain = $_SERVER['HTTP_HOST'];
        $domain = str_replace("www.", PHP_STR, strtolower($domain));
        $isSubdomain = isSubdomainHost($subdomain);
        if ($isSubdomain) {
          $domain = str_replace($subdomain . ".", PHP_STR, $domain);
        }
      }
      
      if ($expire === self::EXPIRE_LIFETIME) {
        $expire = PHP_INT_MAX;
      } elseif (is_numeric($expire)) {
        $expire = time() + $expire;
      } else {
        $expire = strtotime($expire);
      }
      
      $retval = @setcookie(COOKIE_PREFIX . $name, $value, $expire, $path, $domain, false, true);
      if ($retval) {
        $_COOKIE[COOKIE_PREFIX . $name] = $value;
      }
    }
    
    return $retval;
  }

  /**
   * Delete the given cookie
   *
   * @param string $name the name of the cookie
   * @param string $path the path of the cookie
   * @param mixed $domain the domain of the cookie
   * @return bool if the cookie has been successfully deleted, true/false
   */
  static public function delete(string $name, string $path = "/", $domain = false): bool
  {
    $retval = false;
    
    settype($subdomain, "string");
    
    if (!headers_sent())
    {
      if (self::exists($name)) {
        
        if ($domain === false) {
          //$domain = $_SERVER['HTTP_HOST'];
          $domain = $_SERVER['HTTP_HOST'];
          $domain = str_replace("www.", PHP_STR, strtolower($domain));
          $isSubdomain = isSubdomainHost($subdomain);
          if ($isSubdomain) {
            $domain = str_replace($subdomain . ".", PHP_STR, $domain);
          }
        }

        $retval = @setcookie(COOKIE_PREFIX . $name, "", time() - 3600, $path, $domain, false, true);

        unset($_COOKIE[COOKIE_PREFIX . $name]);
      }
    }
    
    return $retval;
  }
}
