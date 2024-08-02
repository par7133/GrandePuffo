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
 * func.file.inc
 * 
 * String related functions.
 *
 * @author Daniele Bonini <my25mb@has.im>
 * @copyrights (c) 2016, 2026 5 Mode
 */

/**
 * Copy a source file
 * 
 * @param string $sourceFilePath the file to copy
 * @param string $destFilePath the destination file
 * @return void
 */
function cp(string $sourceFilePath, string $destFilePath): void 
{
  if (is_readable($sourceFilePath)) {
      $dataLength = 999000;
      $hsfile = fopen($sourceFilePath, "r");
      $hdfile = fopen($destFilePath, "w");
      while ($data = fread($hsfile, $dataLength)) {
        fwrite($hdfile, $data);
      }
      fclose($hsfile);
      fclose($hdfile);
   }   
}


/**
 * Get a new temp file path
 * 
 * @param string $tempResRoot the root path
 * @return string the new tmp file path
 */
function getNewTmpFileName(string $tempResRoot, string $ext): string
{
    chdir($tempResRoot);
    $tmpFileName = "tmp". mt_rand(1000000000, 9999999999) . ".$ext";
    while (is_readable($tmpFileName)) {
       $tmpFileName = "tmp". mp_rand(1000000000, 9999999999) . ".$ext";
    }
    return $tempResRoot . DIRECTORY_SEPARATOR . $tmpFileName;
}
