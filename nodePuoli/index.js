var express = require('express');
var app = express();
var bodyParser = require('body-parser');

var SerialPort = require('serialport');
var ReadLine = SerialPort.parsers.ReadLine;
var port = new SerialPort('/dev/rfcomm2');
//var parser = new ReadLine();

//port.pipe(parser);
//parser.on('data',console.log);



app.get('/testSerial', (req,res) => {
	port.write('#1G000000000000255');
	port.write('#1R000000000000255');
	port.write('#1B000000000000255');
});

app.use(bodyParser.urlencoded({extended:false}))
app.use(bodyParser.json());

app.set('view engine', 'ejs');
app.use(express.static('public'));

app.get('/', (req,res) => {
	res.render('index.ejs');
//	res.send('Hello World!');
});

app.post('/sync', (req,res) => { 
console.log("Vastaanotin dataa:");
console.dir(req.body);
console.log(typeof req.body)
var ledit = JSON.parse(req.body.ledit)

var response = {
    status  : 200,
    success : 'Updated Successfully'
}

res.end(JSON.stringify(response));

//res.status(200); 

paivitaLeditArduinolle(ledit);
} );

function paivitaLeditArduinolle(ledit) {
console.log("Paivita ledit arduinolle");
console.dir(ledit[0].vari[0]);
var l = ledit[0];
console.log("l:");
console.dir(l);

console.log("l.vari:");
// [ '#AB2567', '#AB2567', '#12f445', '#f31200', '#AB2567' ]
console.dir(l.vari);
var variLista;
var varit = [];
for( var i = 0; i < l.vari.length; i++ ) { // Käy jokaisen noden läpi
   var komento = l.vari[i].slice(1); // Otetaan ensimmäinen merkki '#' pois
   console.log("Kasitellaan komento:"+komento);
      
   var R = (('00' + parseInt(komento.slice(0,2),16)).slice(-3));
   var G = (('00' + parseInt(komento.slice(2,4),16)).slice(-3))
   var B = (('00' + parseInt(komento.slice(4,6),16)).slice(-3))
   varit.push([R,G,B]);
}
/* Varit sisältävät esim
//  Rät    Get   Bet
[ '171', '037', '103' ]
[ '171', '037', '103' ]
[ '018', '244', '069' ]
[ '243', '018', '000' ]
[ '171', '037', '103' ]
*/

console.dir("------>"+varit);
console.log("------>"+varit[1]);
console.log("------>"+varit[1][1]);
// Pitää käydä varit läpi ja muotoilla seuraavat lauseet:
//#1R171171018243171
//#1G037037244018037
//#1B103103069000103
   var lauseet = ["#1R","#1G","#1B"];
   for( var t = 0; t < 3; t++) {
   	for( var j = 0; j < varit.length; j++ ) {
		
		console.log("Yhdistän "+varit[j][t]+" lauseeseen "+lauseet[t]);
		lauseet[t] += varit[j][t];   
	}
   }
  console.dir("lauseet:"+lauseet);
  console.log("Lahetetaan:");
  for(var i = 0; i < lauseet.length; i++) {	
	port.write(lauseet[i]);
}
  console.dir(varit);
}

app.listen(3333, () => { console.log("Running on 3333"); });
