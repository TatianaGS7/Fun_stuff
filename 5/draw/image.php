<?php 
if (isset($_GET['x'])&&$_GET['x']!='' ) {
	$x = $_GET['x'];
 	$Array = explode('_', $x);

 	$start_x = 40;
 	$start_y = 100;
 	$start_x_sky = 40;
 	$start_y_sky = 100;
 	$img = imagecreatetruecolor(1000, 400);
 	$colored = 0;

 	$scale = 1;

 	$in = 0;
 	$upon = 0;

 	$many = 0;

 	$broken = 0;
	imagefill($img, 0, 0, 0x60C6E8);
	imagefilledrectangle($img, 0, 300,1000, 400, 0xB17F4A);

 	for ($i=0; $i < count($Array); $i++) {
 		if ($Array[$i]=='цветной'||$Array[$i]=='цветном'||$Array[$i]=='цветное'||$Array[$i]=='цветного') {
 				$colored = 1;
 		}
 		if ($Array[$i]=='в') {
 				$in = 1;
 		}
 		if ($Array[$i]=='на') {
 				$upon = 1;
 		}
 		if ($Array[$i]=='большой'||$Array[$i]=='большом'||$Array[$i]=='большая'||$Array[$i]=='большое') {
 			$scale = 1.5;
 		}
 		if ($Array[$i]=='маленький'||$Array[$i]=='маленьком'||$Array[$i]=='маленькой'||$Array[$i]=='маленькое') {
 			$scale = 0.5;
 		}
 		if ($Array[$i]=='много') {
 			$many = 1;
 		}
 		if ($Array[$i]=='сломанный') {
 				$broken = 0.96;
 		}

 		if ($Array[$i]=='солнце'||$Array[$i]=='солнце') {
 			if ($colored == 0) {
 				
 				
 				if ($in != 0) {
 					if ($in == 2) {
		 				imagearc($img, $start_x_sky, $start_y_sky, 50/2*$scale, 50/2*$scale, 0, 360, 0xFDFA91);
		 				$in = 0;
		 				$start_x_sky = $start_x_sky + 70;
		 				if ($scale != 1) {
		 					$scale = 1;
		 				}
		 			}elseif ($in == 1) {
		 				imagearc($img, $start_x_sky, $start_y_sky, 50*$scale, 50*$scale, 0, 360, 0xFDFA91);
		 				$in = 2;
		 				if ($scale != 1) {
		 					$scale = 1;
		 				}
		 			}

 				} elseif($upon!= 0){
 					if ($upon == 2) {
		 				imagearc($img, $start_x_sky, $start_y_sky-50, 50*$scale, 50*$scale, 0, 360, 0xFDFA91);
		 				$upon = 0;
		 				$start_x_sky = $start_x_sky + 70;
		 				if ($scale != 1) {
		 					$scale = 1;
		 				}
		 			}elseif ($upon == 1) {
		 				imagearc($img, $start_x_sky, $start_y_sky, 50*$scale, 50*$scale, 0, 360, 0xFDFA91);
		 				$upon = 2;
		 				if ($scale != 1) {
		 					$scale = 1;
		 				}
		 			}
	 			
 				} else{
 					imagearc($img, $start_x_sky, $start_y_sky, 50*$scale, 50*$scale, 0, 360, 0xFDFA91);
	 					$start_x_sky = $start_x_sky + 70;
	 					if ($scale != 1) {
		 					$scale = 1;
		 				}
 				}
 				


 				
	 			

 			} else {
 				
 				if ($in != 0) {
 					if ($in == 2) {
		 				imagefilledarc($img, $start_x_sky, $start_y_sky, 50/2*$scale, 50/2*$scale, 0, 360, 0xFDFA91,IMG_ARC_PIE);
		 				$in = 0;
		 				$start_x_sky = $start_x_sky + 70;
		 				if ($scale != 1) {
		 					$scale = 1;
		 				}
		 			}elseif ($in == 1) {
		 				imagefilledarc($img, $start_x_sky, $start_y_sky, 50*$scale, 50*$scale, 0, 360, 0xFDFA91,IMG_ARC_PIE);
		 				$in = 2;
		 				if ($scale != 1) {
		 					$scale = 1;
		 				}
		 			}

 				} elseif($upon!= 0){
 					if ($upon == 2) {
		 				imagefilledarc($img, $start_x_sky, $start_y_sky-50, 50*$scale, 50*$scale, 0, 360, 0xFDFA91,IMG_ARC_PIE);
		 				$upon = 0;
		 				$start_x_sky = $start_x_sky + 70;
		 				if ($scale != 1) {
		 					$scale = 1;
		 				}
		 			}elseif ($upon == 1) {
		 				imagefilledarc($img, $start_x_sky, $start_y_sky, 50*$scale, 50*$scale, 0, 360, 0xFDFA91,IMG_ARC_PIE);
		 				$upon = 2;
		 				if ($scale != 1) {
		 					$scale = 1;
		 				}
		 			}
	 			
 				} else{
 					imagefilledarc($img, $start_x_sky, $start_y_sky, 50*$scale, 50*$scale, 0, 360, 0xFDFA91,IMG_ARC_PIE);
	 					$start_x_sky = $start_x_sky + 70;
	 					if ($scale != 1) {
		 					$scale = 1;
		 				}
 				}
 				
	 			$colored = 0;
 			}
 		}
 		if ($Array[$i]=='трава'||$Array[$i]=='травы') {
 			if ($colored == 1) {
	 			
	 			if ($many == 1) {
	 				$num = 1900;
	 			} else {
	 				$num = 300;
	 			}
	 			$otr = 1000/$num;
	 			for ($t=0; $t < $num; $t++) { 
	 				$colorr = "0x709C3".rand(0,20);
					imageline($img, 0+$otr*$t+rand(0,10), 300+rand(0,10), 2+$otr*$t+rand(0,10), 310-rand(-20,20)-$scale*20, $colorr);
				}
				if ($scale != 1) {
	 					$scale = 1;
	 				}
				$many = 0;
			} else{
				if ($many == 1) {
	 				$num = 1900;
	 			} else {
	 				$num = 300;
	 			}
	 			$otr = 1000/$num;
	 			for ($t=0; $t < $num; $t++) { 
	 				
					imageline($img, 0+$otr*$t+rand(0,10), 300+rand(0,10), 2+$otr*$t+rand(0,10), 310-rand(-20,20)-$scale*20, 0x709C38);
				}
				if ($scale != 1) {
		 					$scale = 1;
		 				}
				$many = 0;
			}
 		}
 		if ($Array[$i]=='дождь'||$Array[$i]=='дождя') {
 			if ($colored == 1) {
	 			
	 			if ($many == 1) {
	 				$num = 4000;
	 			} else {
	 				$num = 1000;
	 			}
	 			
	 			for ($t=0; $t < $num; $t++) { 
	 				$colorr = "0x7".rand(0,8).rand(0,8).rand(0,8).rand(0,8).rand(0,8);
					imagesetpixel($img, rand(0,1000),rand(0,300),$colorr);
				}
				$colored = 0;
				$many = 0;
			} else{
				if ($many == 1) {
	 				$num = 4000;
	 			} else {
	 				$num = 1010;
	 			}
	 			
	 			for ($t=0; $t < $num; $t++) { 
	 				
					imagesetpixel($img, rand(0,1000),rand(0,300),0x78797D);
				}
				
				$many = 0;
			}
 		}
 		if ($Array[$i]=='дом'||$Array[$i]=='доме') {
 			if ($colored == 0) {
	 		
	 			imagefilledrectangle($img, $start_x+1*$scale, $start_y+100, $start_x+100*$scale, $start_y+200, 0x78797D);
	 			imagefilledrectangle($img, $start_x+25*$scale, $start_y+130, $start_x+75*$scale, $start_y+170, 0x287EBF);
	 			imagefilledrectangle($img, $start_x-10*$scale, $start_y+90, $start_x+110*$scale, $start_y+100, 0x825733);
	 			imagefilledrectangle($img, $start_x+20*$scale, $start_y+70, $start_x+80*$scale, $start_y+80, 0x825733);
	 			imagefilledrectangle($img, $start_x+10*$scale, $start_y+80, $start_x+90*$scale, $start_y+90, 0x825733);
	 			$start_x = $start_x + 140*$scale;
	 			if ($scale != 1) {
			 		$scale = 1;
			 	}
			 	
			 } else {
			 	imagefilledrectangle($img, $start_x+1*$scale, $start_y+100, $start_x+100*$scale, $start_y+200, 0xE8A231);
	 			imagefilledrectangle($img, $start_x+25*$scale, $start_y+130, $start_x+75*$scale, $start_y+170, 0x287EBF);
	 			imagefilledrectangle($img, $start_x-10*$scale, $start_y+90, $start_x+110*$scale, $start_y+100, 0xBD3B05);
	 			imagefilledrectangle($img, $start_x+20*$scale, $start_y+70, $start_x+80*$scale, $start_y+80, 0xBD3B05);
	 			imagefilledrectangle($img, $start_x+10*$scale, $start_y+80, $start_x+90*$scale, $start_y+90, 0xBD3B05);
	 			$start_x = $start_x + 140*$scale;
	 			if ($scale != 1) {
			 		$scale = 1;
			 	}
			 	
			 	$colored = 0;
			 }
 		}
 		if ($Array[$i]=='шар') {
 			if ($colored == 0) {
 				$r = 0;
 				if ($scale > 1) {
 					$start_x = $start_x + 20;
 					$r = 12;
 				}
 				imagefilledarc($img, $start_x, $start_y+187-$r, 50/1*$scale, 50/1*$scale, 0, 360*$broken, 0xFBFDFF,IMG_ARC_PIE);
 				imagefilledarc($img, $start_x+rand(3*$scale,8*$scale), $start_y+187+rand(3*$scale,8*$scale), 50/5*$scale, 50/5*$scale, 0, 360, 0x0A0F0E,IMG_ARC_PIE);
 				imagefilledarc($img, $start_x-rand(3*$scale,8*$scale), $start_y+187-rand(3*$scale,8*$scale), 50/5*$scale, 50/5*$scale, 0, 360, 0x0A0F0E,IMG_ARC_PIE);
 				imagefilledarc($img, $start_x+rand(3*$scale,8*$scale), $start_y+187-rand(3*$scale,8*$scale), 50/5*$scale, 50/5*$scale, 0, 360, 0x0A0F0E,IMG_ARC_PIE);
 				// imagefilledarc($img, $start_x-rand(3*$scale,10*$scale), $start_y+187+rand(3*$scale,10*$scale), 50/5*$scale, 50/5*$scale, 0, 360, 0x0A0F0E,IMG_ARC_PIE);
 				$start_x = $start_x + 90*$scale;
	 			if ($scale != 1) {
			 		$scale = 1;
			 	}
			 	$broken = 0;
 			} else{
 				$r = 0;
 				if ($scale > 1) {
 					$start_x = $start_x + 20;
 					$r = 12;
 				}
 				imagefilledarc($img, $start_x, $start_y+187-$r, 50/1*$scale, 50/1*$scale, 0, 360*$broken, 0x9F52E8,IMG_ARC_PIE);
 				imagefilledarc($img, $start_x+rand(3*$scale,10*$scale), $start_y+187+rand(3*$scale,10*$scale)-$r, 50/5*$scale, 50/5*$scale, 0, 360, 0xFFF007,IMG_ARC_PIE);
 				imagefilledarc($img, $start_x-rand(3*$scale,10*$scale), $start_y+187-rand(3*$scale,10*$scale)-$r, 50/5*$scale, 50/5*$scale, 0, 360, 0xFFBD06,IMG_ARC_PIE);
 				imagefilledarc($img, $start_x+rand(3*$scale,10*$scale), $start_y+187-rand(3*$scale,10*$scale)-$r, 50/5*$scale, 50/5*$scale, 0, 360, 0x87FF06,IMG_ARC_PIE);
 				// imagefilledarc($img, $start_x-rand(3*$scale,10*$scale), $start_y+187+rand(3*$scale,10*$scale), 50/5*$scale, 50/5*$scale, 0, 360, 0xFF9413,IMG_ARC_PIE);
 				$start_x = $start_x + 90*$scale;
	 			if ($scale != 1) {
			 		$scale = 1;
			 	}
 				$colored = 0;
 				$broken = 0;
 			}

 		}
 	}

	
	


	header("Content-type: image/png");
	imagepng($img);
	imagedestroy($img);
} else{
	$img = imagecreatetruecolor(1000, 400);
	imagefill($img, 0, 0, 0xE8CBB7);
	
	header("Content-type: image/png");
	imagepng($img);
	imagedestroy($img);
}
 ?>