var n=0;
var reseta=0;

function slika()
{	
	let slika;
	switch (reseta%3) {
		case 0: 
		slika = `<img src="https://cdn.discordapp.com/attachments/923107407796797451/934539399683772506/IMG_3131.jpg">`;
		break;
		case 1:
		slika = `<img src="https://i2.wp.com/navbharattimes.indiatimes.com/thumb/msid-76340536,width-1200,height-630/pic.jpg">`;
		break;
		case 2:
		slika = `<img src="https://cdn.discordapp.com/attachments/917098364787650590/935156371547103282/Screenshot_20211211-205126_One_UI_Home_1.png">`;
		break;
	}
	document.getElementById("abc").innerHTML = slika;
	n=0;
}

function tekst()
{
	document.getElementById("abc").innerHTML = "Kliknuli ste ovo dugme " + (++n) + " put" + (n!=1?"a":"") + " za redom.";
}

function brisi()
{
	window.alert("Obrisano.\nPrikazace se nova slika!");
	document.getElementById("abc").innerHTML = "Nista nije prikazano";
	n=0;
	reseta++;
}