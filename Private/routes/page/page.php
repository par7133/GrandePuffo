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
 * page.php
 * 
 * The Page.
 *
 * @author Daniele Bonini <my25mb@has.im>
 * @copyrights (c) 2016, 2026 5 Mode     
 */

$myPrefix= mt_rand(1000000, 1199999);
$myImageSha = "ba78c55eae177c8e6749fa6aded78757ccfb10c85121cb4fbbb76b9ce3ef4db2";

?>

<html>
<head>
<link src="style1.css" type="text/css">
</head>
<body>
<img src='/<?PHP echo($myPrefix.$myImageSha);?>'>
<img src='/<?PHP echo($myPrefix.$myImageSha);?>'>
<img src='/<?PHP echo($myPrefix.$myImageSha);?>'>
<img src='/<?PHP echo($myPrefix.$myImageSha);?>'>
<img src='/<?PHP echo($myPrefix.$myImageSha);?>'>
</body>
</html>
