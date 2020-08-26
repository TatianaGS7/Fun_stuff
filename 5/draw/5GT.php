<?php 
if (isset($_GET['x'])&&$_GET['x']!='' ) {
	$x = $_GET['x'];
 	$Array = explode('_', $x);

 	$start_x_sky = 140;
 	$start_y_sky = 70;

	// создание пустого изображения
 	$img = imagecreatetruecolor(450, 400);
 	// заливка фона прозрачным
	$bl = imagecolorallocate($img, 0, 0, 0);
	imagecolortransparent($img, $bl);


 	$scale = 1;
    $biglun = 0;
    $near = 0;
	$under = 0;
 	$manykon = 0;
 	$color1 = 0;
 	$color2 = 0;

 	//Цвета
 	$nit = imagecolorallocate($img, 72, 61, 139); //нить у шарика
	$luna = imagecolorallocate($img, 255, 221, 130);
	$star= imagecolorallocate($img, 255, 250, 205);// выбор цвета для  звезды
	$bigl = imagecolorallocate($img, 106, 90, 205); //Шарик
    $sml = imagecolorallocate($img, 132, 112, 255);
    $black = imagecolorallocate($img, 11, 4, 11);
    $purp = imagecolorallocate($img, 170, 30, 230);




//Нахождение команд

 	for ($i=0; $i < count($Array); $i++) {

 		if ($Array[$i]=='Черная'||$Array[$i]=='черная'||$Array[$i]=='Чёрная'||$Array[$i]=='чёрная') {
 				$color1 = 1;
 		}
        
 		if ($Array[$i]=='под') {
 				$near = 1;
 		}
        
         if ($Array[$i]=='Восходит' || $Array[$i]=='восходит') {
 				$under = 1;
 		}

 		if ($Array[$i]=='Пурпурная'||$Array[$i]=='пурпурная') {
 				$color2 = 1;
 		}
 		if ($Array[$i]=='большой'||$Array[$i]=='Большой') {
 			$scale = 1.5;
 		}

 		if ($Array[$i]=='многоконечная') {
 			$manykon = 1;
 		}

 		if ($Array[$i]=='большая'||$Array[$i]=='Большая') {
 			$biglun = 1;
 		}


  //Луна
 		if ($Array[$i]=='луна'||$Array[$i]=='Луна') {
 			if ($biglun == 1) {
 					if($color1 == 1){
 						if ($under == 1) {
                  imagefilledellipse($img, $start_x_sky-10, $start_y_sky+130, 60*1.3, 60*1.3, $black);}
 					 
 					else {
 					imagefilledellipse($img, $start_x_sky, $start_y_sky, 60*1.3, 60*1.3, $black);}
 				                  }
 						else{
 							if ($under == 1) {
 					imagefilledellipse($img, $start_x_sky-10, $start_y_sky+130, 60*1.3, 60*1.3, $luna);
 							}
 							else{
 						imagefilledellipse($img, $start_x_sky, $start_y_sky, 60*1.3, 60*1.3, $luna);}
 
 							}
					    }

		 			else {
                     if($color1 == 1){
                     	if ($under == 1) {
                    imagefilledellipse($img, $start_x_sky-10, $start_y_sky+130, 60, 60, $black);}
                       else{
                           imagefilledellipse($img, $start_x_sky, $start_y_sky, 60, 60, $black);}
 						}
 						else{
 							if ($under == 1) {
                    imagefilledellipse($img, $start_x_sky-10, $start_y_sky+130, 60, 60, $luna);}
                	else{imagefilledellipse($img, $start_x_sky, $start_y_sky, 60, 60, $luna);}
 
 						}
 	
		 			}

 				} 


 //Звезда		
 		if ($Array[$i]=='звезда'||$Array[$i]=='Звезда') {
 	 				if ($manykon == 1) {

 	 				if($color2 == 1){
	 				$num = 10;
	 				$vs1 = array(
			19,  25,  // Point 1 (x, y)
            30,  25, // Point 2 (x, y)
            35, 14,  // Point 3 (x, y)
            40, 25,  // Point 4 (x, y)
            50, 25,  // Point 5 (x, y)
            40, 30,  // Point 6 (x, y)
            47, 41,  // Point 7 (x, y)
            35, 35,  // Point 8 (x, y)
            22, 41,  // Point 9 (x, y)
            30, 30,  // Point 10 (x, y)   
                               );
			imagefilledpolygon($img, $vs1, $num, $purp);
                    }
              else{
              		$num = 10;
	 				$vs1 = array(
			19,  25,  // Point 1 (x, y)
            30,  25, // Point 2 (x, y)
            35, 14,  // Point 3 (x, y)
            40, 25,  // Point 4 (x, y)
            50, 25,  // Point 5 (x, y)
            40, 30,  // Point 6 (x, y)
            47, 41,  // Point 7 (x, y)
            35, 35,  // Point 8 (x, y)
            22, 41,  // Point 9 (x, y)
            30, 30,  // Point 10 (x, y)   
                               );
			imagefilledpolygon($img, $vs1, $num, $star);
              }
	 			} 
	 			else {
	 				if($color2 == 1){
	 				$num = 6;
	 				$vs2 = array(
			24,  25,  // Point 1 (x, y)
            27,  40, // Point 2 (x, y)
            30, 28,  // Point 3 (x, y)
            42, 16,  // Point 4 (x, y)
            27,  22,  // Point 5 (x, y)
            15,  13   // Point 6 (x, y)
            );

			imagefilledpolygon($img, $vs2, $num, $purp);
		}
		else{
			$num = 6;
	 		$vs2 = array(
			24,  25,  // Point 1 (x, y)
            27,  40, // Point 2 (x, y)
            30, 28,  // Point 3 (x, y)
            42, 16,  // Point 4 (x, y)
            27,  22,  // Point 5 (x, y)
            15,  13   // Point 6 (x, y)
            );
			imagefilledpolygon($img, $vs2, $num, $star);
		}
			}
	 			
	 			$manykon = 0;	
	 			$color2 = 0;		
			 		}


  //Шар
 		if ($Array[$i]=='Шар'||$Array[$i]=='Шарик'||$Array[$i]=='шар'||$Array[$i]=='шарик'||$Array[$i]=='Воздушный шарик'||$Array[$i]=='Воздушный шар'||$Array[$i]=='воздушный шар'||$Array[$i]=='воздушный шарик') {
 			if ($scale == 1.5) {
	 		     if ($near == 1) {
		 		// рисование  эллипса
	 			imagefilledellipse($img, 370, 200+60, 50*1.2, 80*1.2, $bigl);
                imagefilledellipse($img, 360, 180+60, 10*1.2, 20*1.2, $sml);
                //рисование треугольника
			$values = array(
            363,  255+60,  // Point 1 (x, y)
            377, 255+60, // Point 2 (x, y)
            372,  240+60,  // Point 3 (x, y)
            );

			imagefilledpolygon($img, $values, 3, $bigl);
			//Рисование ниточки
			imagesetthickness($img, 3);
			$x11 = 380;
			$y11 = 280+60;
			$x21 = 369;
			$y21= 256+60;
			imageline ( $img , $x11 , $y11 , $x21 , $y21 , $nit);

			$x12 = 410;
			$y12 = 300+60;
			$x22 = 380;
			$y22= 280+60;
			imageline ( $img , $x12 , $y12 , $x22 , $y22 , $nit);

		 	}
		 	else{
		 		// рисование  эллипса
	 			imagefilledellipse($img, 370-10, 200-150, 50*1.2, 80*1.2, $bigl);
                imagefilledellipse($img, 360-10, 180-150, 10*1.2, 20*1.2, $sml);
                //рисование треугольника
			$values = array(
            363-10,  255-150,  // Point 1 (x, y)
            377-10, 255-150, // Point 2 (x, y)
            372-10,  240-150,  // Point 3 (x, y)
            );

			imagefilledpolygon($img, $values, 3, $bigl);
			//Рисование ниточки
			imagesetthickness($img, 3);
			$x11 = 380-10;
			$y11 = 280-150;
			$x21 = 369-10;
			$y21= 256-150;
			imageline ( $img , $x11 , $y11 , $x21 , $y21 , $nit);

			$x12 = 410-10;
			$y12 = 300-150;
			$x22 = 380-10;
			$y22= 280-150;
			imageline ( $img , $x12 , $y12 , $x22 , $y22 , $nit);

		 	}
			 } else {
			 	if ($near == 1) {
	 		     // рисование  эллипса
	 			imagefilledellipse($img, 370+10, 200+70, 50, 80, $bigl);
                imagefilledellipse($img, 360+10, 180+70, 10, 20, $sml);
                //рисование треугольника
			$values = array(
            363+11,  255+65,  // Point 1 (x, y)
            377+10, 255+65, // Point 2 (x, y)
            372+10,  240+65,  // Point 3 (x, y)
            );

			imagefilledpolygon($img, $values, 3, $bigl);
			//Рисование ниточки
			imagesetthickness($img, 3);
			$x11 = 380+10;
			$y11 = 280+65;
			$x21 = 369+11;
			$y21= 256+65;
			imageline ( $img , $x11 , $y11 , $x21 , $y21 , $nit);

			$x12 = 410+10;
			$y12 = 300+65;
			$x22 = 380+10;
			$y22= 280+65;
			imageline ( $img , $x12 , $y12 , $x22 , $y22 , $nit);
		}
		else{
				 // рисование  эллипса
	 			imagefilledellipse($img, 370-10, 200-150, 50, 80, $bigl);
                imagefilledellipse($img, 360-10, 180-150, 10, 20, $sml);
                //рисование треугольника
			$values = array(
            363-8,  255-155,  // Point 1 (x, y)
            377-10, 255-155, // Point 2 (x, y)
            372-10,  240-155,  // Point 3 (x, y)
            );

			imagefilledpolygon($img, $values, 3, $bigl);
			//Рисование ниточки
			imagesetthickness($img, 3);
			$x11 = 380-10;
			$y11 = 280-155;
			$x21 = 369-8;
			$y21= 256-155;
			imageline ( $img , $x11 , $y11 , $x21 , $y21 , $nit);

			$x12 = 410-10;
			$y12 = 300-155;
			$x22 = 380-10;
			$y22= 280-155;
			imageline ( $img , $x12 , $y12 , $x22 , $y22 , $nit);
		}

			 }
 		}
 		 	}

	//выводим рисунок
	header("Content-type: image/png");
	imagepng($img);
	imagedestroy($img);
} 
else{

		// создание пустого изображения
 	$img = imagecreatetruecolor(450, 300);
 	// заливка фона прозрачным
	$bl = imagecolorallocate($img, 0, 0, 0);
	imagecolortransparent($img, $bl);
    header("Content-type: image/png");
	imagepng($img);
	imagedestroy($img);
}
 ?>