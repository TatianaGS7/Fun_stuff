<?php
//Луна
$im = imagecreatetruecolor(300, 300);
$luna = imagecolorallocate($im, 255, 221, 130);
$black = imagecolorallocate($im, 0, 0, 0);
imagecolortransparent($im, $black);
imagefilledellipse($im, 100, 100, 80, 80, $luna);



//Шарик
// создание пустого изображения
$image = imagecreatetruecolor(400, 300);

// заливка фона прозрачным
$bl = imagecolorallocate($image, 0, 0, 0);
imagecolortransparent($image, $bl);
// выбор цвета для эллипса
$bigl = imagecolorallocate($image, 106, 90, 205);
$sml = imagecolorallocate($image, 132, 112, 255);

// рисование  эллипса
imagefilledellipse($image, 90, 100, 50, 80, $bigl);
imagefilledellipse($image, 80, 80, 10, 20, $sml);

//рисование треугольника
$values = array(
            83,  150,  // Point 1 (x, y)
            100, 150, // Point 2 (x, y)
            92,  120,  // Point 3 (x, y)
            );

imagefilledpolygon($image, $values, 3, $bigl);

//Рисование ниточки
$nit = imagecolorallocate($image, 72, 61, 139);
imagesetthickness($image, 3);
$x11 = 98;
$y11 = 180;
$x21 = 93;
$y21= 150;
imageline ( $image , $x11 , $y11 , $x21 , $y21 , $nit);

$x12 = 123;
$y12 = 210;
$x22 = 98;
$y22= 180;
imageline ( $image , $x12 , $y12 , $x22 , $y22 , $nit);



//Звезда
// создание пустого изображения
$image2 = imagecreatetruecolor(200, 200);

// заливка фона прозрачным
$bls = imagecolorallocate($image2, 0, 0, 0);
imagecolortransparent($image2, $bls);
// выбор цвета для  звезды
$star= imagecolorallocate($image2, 255, 250, 205);


//рисование треугольника
$vs = array(
			9,  15,  // Point 1 (x, y)
            12,  30, // Point 2 (x, y)
            15, 18,  // Point 3 (x, y)
            27, 6,  // Point 4 (x, y)
            12,  12,  // Point 5 (x, y)
            0,  3   // Point 6 (x, y)
            );

imagefilledpolygon($image2, $vs, 6, $star);




// вывод картинки

imagecopymerge($im, $image, 90, 10, 40, 0, 200, 200, 90);

header("Content-type: image/png");

imagepng($im);
imagedestroy($im);

imagedestroy($image);

?>