$(function (){
//Построение линейной регрессионной модели Y=AX+B  по массиву исходных данных XY
var A;
var B;
var XY=[ [0,-0.861],[1,-0.007],[2,1.044],[3,2.138],[4,3.105],[5,4.077],[6,5.177],
 [7,6.073],[8, 7.160],[9,8.087],[10,8.828] ]; //Исходные данные

var XYT; //Транспортированная матрица исходных данных
var X; //Вектор исходных значений Х
var Y; //Вектор исходных значений Y
var N; //Длина массива данных
var SUM_X; //Сумма X
var SUM_Y; //Сумма Y
var SUM_X_SQR; //Сумма квадратов X
var SUM_XY; //Сумма  произведений x[i]*y[i]
var M; //Матрица СЛАУ
var INVM; //Обратная матрица
var F;//Вектор свободных членов
var R;//Решение СЛАУ
var SSUMSQR;//Среднее отклонение


//Определение длины исходного массива
N=XY.length;

//Вычисление векторов X,Y
XYT=numeric.transpose(XY);
X=XYT[0];
Y=XYT[1];
//Вычисление матрицы СЛАУ
SUM_X=numeric.sum(X);
SUM_Y=numeric.sum(Y);
SUM_X_SQR=numeric.sum(numeric["*"](X,X));
SUM_XY=numeric.sum(numeric["*"](X,Y));

M=[[SUM_X_SQR,SUM_X],[SUM_X,N]]; //Матрица системы

//Решение системы
INVM=numeric.inv(M);
F=[[SUM_XY],[SUM_Y]];
R=numeric.dot(INVM,F);
A=R[0][0];
B=R[1][0];

//Среднее отклонение
SSUMSQR=numeric.norm2(
numeric["+"](
    numeric["*"](A,X),
    B,
    numeric["*"](-1,Y)
		)
	)/Math.sqrt(N);


$.plot($("#placeholder"),[
{
	data: [[X[0],A*X[0]+B],[X[10],A*X[10]+B]],
	label:"Y=AX+B",
	points:{show:false},
	lines:{show: true, fill: false}
},
{
	data: XY,
	label:"Данные(X,Y)",
	points:{show:true},
	lines:{show: false, fill: false}
}
]);

document.getElementById("t1").value = A;
document.getElementById("t2").value = B;
document.getElementById("t3").value = SSUMSQR;

 //alert('A='+A+'B='+B+'SSUMSQR='+SSUMSQR);

});

