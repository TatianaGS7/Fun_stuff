<html>
<head>
	<title>1</title>
	<meta charset = "utf-8">
</head>
<body id = 'body'>
	<div style = 'position:absolute;  right:10px;'>v 2.1</div>
	<style type="text/css">
		
		#button{
			height: 40px;
			width:600px;
			background-color: #80AB9F;
			color: #46635D;
			margin-top: 10px;
			border-radius: 3px 3px 3px 3px;
			-moz-border-radius: 3px 3px 3px 3px;
			-webkit-border-radius: 3px 3px 3px 3px;
			text-align: center;
			font-family: 'Helvetica Neue',Helvetica,sans-serif;
			font-size: 25px;
			margin-right: auto;
			margin-left: auto;
			padding-top: 10px;
		}
		#button:hover{
			height: 40px;
			width:600px;
			background-color: #9CBBA9;
			
		}
		#text {
			width: 1000px;
			height: 80px;
			border-radius: 3px 3px 3px 3px;
			-moz-border-radius: 3px 3px 3px 3px;
			-webkit-border-radius: 3px 3px 3px 3px;
			border: 1px solid #545046;
			font-family: 'Helvetica Neue',Helvetica,sans-serif;
			font-size: 25px;
			max-width: 1000px;
			color: #7f8c8d;
			margin-top: 10px;
		}
		body{
			background-color: #FDF4D7;
		}
		table{
			font-family: 'Helvetica Neue',Helvetica,sans-serif;
			font-size: 16px;
			border-collapse: collapse;
			 border: 2px solid #46635D;
			 width: 1000px;
			color: #46635D;
			margin-bottom: 20px;
		}
		tr{
			border: 2px solid #46635D;
		}
		td{
			border: 2px solid #46635D;
			
		}
		#img{
			border-radius: 10px 10px 10px 10px;
			-moz-border-radius: 10px 10px 10px 10px;
			-webkit-border-radius: 10px 10px 10px 10px;
			-webkit-box-shadow: 1px 1px 12px 0px rgba(0,0,0,0.75);
			-moz-box-shadow: 1px 1px 12px 0px rgba(0,0,0,0.75);
			box-shadow: 1px 1px 12px 0px rgba(0,0,0,0.75);
			margin-top: 10px;
			
		}
		#all{
			
			margin-left: auto;
			margin-right: auto;
			width: 1000px;
			
		}
		#instruction{
			margin-top: 20px;
			float: left;
			margin-left: 15px;
			font-family: 'Helvetica Neue',Helvetica,sans-serif;
			font-size: 25px;
			color: white;
			width: 1000px;
		}
	</style>
	<div id = 'all_wr'>
		<div id = 'all'>
			
			
			<img src="image.php" id = 'img'>
			<textarea id = 'text'></textarea><div id = 'button' onclick = 'takeImg();'>Получить изображение</div>
			<hr>
		<div id = 'instruction'>
				<table>

					<tr>
						<td style = 'font-size:23px; text-align:center'>Объект</td>
						<td style = 'font-size:23px; text-align:center;'>Модификаторы</td>
						

					</tr>
					<tr>
						<td>солнце</td>
						<td>в, на, цветное, большое, маленькое</td>
						
					</tr>	
					<tr>
						<td>трава</td>
						<td>цветная, много, большая, маленькая</td>
						
					</tr>
					<tr>
						<td>дождь</td>
						<td>цветной, много</td>
						
					</tr>
					
					<tr>
						<td>дом</td>
						<td>большой, маленький, цветной</td>
						
					</tr>
					<tr>
						<td>шар</td>
						<td>большой, маленький, цветной, сломанный</td>
						
					</tr>
					<tr>
						<td>Модификаторы в, на, пишутся: В .1. .2. , где 1 - объект в котором находится второй объект</td>
					</tr>
					
				</table>
		</div>
		</div>

	</div>
	<script type="text/javascript">
		function takeImg(){
			var request = document.getElementById('text');
			var requestText = request.value;
			requestText =requestText.replace(/ /g,"_");

			var img = document.getElementById('img');
			img.setAttribute('src','image.php?x='+requestText);
			
		}
		// var body = document.getElementById('body');
		// client_w=document.body.clientWidth;
		// client_h=document.body.clientHeight;
		// body.setAttribute('style', "background-image:url('image2.php?x="+client_w+"&y="+client_h+"');");

	</script>

</body>
</html>