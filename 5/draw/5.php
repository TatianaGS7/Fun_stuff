<!DOCTYPE html>
<html>
<head>
<meta charset = "utf-8">
	<title>Pic</title>
<style>
   body {
   	background: #FFFF99; 
    background-image: url(Pur.png);
    background-repeat: no-repeat;
    position:absolute;
   }
     
     .fr{
       float:left;
     }
    
</style>
	</head>

<body>



<div class="fr"><img src = "5GT.php" id='img'></div>

<form>
		<input type='text' id = 'text1' name = 'command' size= 50px>
		<input type='button' value = 'Рисовать' onclick = 'draw();'>
</form>

 <table border="2" style = 'text-align: center; border-style: double; margin-left: 600px;'>
   <caption><abbr title="Показывает, какие можно применять объекты и с какими модификациями. Следует писать сначала модификацию, потом объект">Инструкция</abbr></caption>
     <th><abbr title="При написании этих объектов можно писать с заглавной буквы">Динамические объекты</abbr></th>
     <tr><td><abbr title="Луна или луна">Луна</td></tr>  
     <tr><td><abbr title="Шар,Шарик,шар,шарик,Воздушный шарик,Воздушный шар,воздушный шар,воздушный шарик">Воздушный шар</abbr></td></tr>
      <tr><td><abbr title="звезда или Звезда">Звезда</abbr></td></tr>
    <tr><th><abbr title="При написании этих объектов можно писать с заглавной буквы,также допускатеся использование буквы ё">Модификация</abbr></th></tr>
       <tr><td><abbr title="Черная,черная,Чёрная,чёрная">Черный цвет(Луна)</abbr></td></tr>
       <tr><td><abbr title="Пурпурная или пурпурная">Пурпурный цвет (Звезда)</abbr></td></tr>
   <tr><td>многоконечная Звезда</td></tr>
   <tr><td><abbr title="Применяется к Шару">под (Шар)</abbr></td></tr>
   <tr><td><abbr title="Восходит или восходит">восходит (Луна)</abbr></td></tr>
    <tr><td><abbr title="большая или Большая,большой или Большой">большая (Луна),большой (Шар)</abbr></td></tr>
    </table>


<script type="text/javascript">
		function draw(){
			var request = document.getElementById('text1');
			var requestText = request.value;
			requestText =requestText.replace(/ /g,"_");

			var img = document.getElementById('img');
			img.setAttribute('src','5GT.php?x='+requestText);
			
		}
		// var body = document.getElementById('body');
		// client_w=document.body.clientWidth;
		// client_h=document.body.clientHeight;
		// body.setAttribute('style', "background-image:url('image2.php?x="+client_w+"&y="+client_h+"');");

	</script>



</body>
</html>