var listaTelefona

function ucitaj(telefon) {
	document.title = "Rectel"
	$.each(listaTelefona, function (id, telefon) {
		$("#navbarList").append(`
            <li>
                <a href="telefon.html?idtel=${telefon._id}">${telefon.ime}</a>
            </li>
		`)
	})

	if (telefon !== undefined) {
		document.title = "Rectel - " + telefon.ime
		$("#naslov").text(`
			${telefon.ime}
		`)
		$("#dodatnaRecenzija").html(`
			<a href="${telefon.punarecenzija}" target="_blank">Puna recenzija</a>
		`)
		$("#video").html(`
			<iframe class="embed-responsive-item" src="${telefon.recenzija}"></iframe>
		`)
		$("#slika").html(`
			<img class="phone" src="${telefon.slika}" alt="${telefon.title}"/>
		`)
		const brojocena = telefon.komentari.length
		if (brojocena == 0) {
			$("#prosecnaOcena").append("/")
		} else {
			var total = 0
			for (i = 0; i < brojocena; i++) {
				total += telefon.komentari[i].ocena
			}
			$("#prosecnaOcena").append(total/brojocena)
		}
		$("#specifikacije").html(`
			<tbody>
			<tr>
				<td>Cena</td>
				<td>${telefon.specs.cena}</td>
			</tr>
			<tr>
				<td>Kamera</td>
				<td>${telefon.specs.kamera}</td>
			</tr>
			<tr>
				<td>Mreza</td>
				<td>${telefon.specs.mreza}</td>
			</tr>
			<tr>
				<td>Datum objave</td>
				<td>${telefon.specs.datumobjave}</td>
			</tr>
			<tr>
				<td>Ekran</td>
				<td>${telefon.specs.ekran}</td>
			</tr>
			<tr>
				<td>Operativni sistem</td>
				<td>${telefon.specs.os}</td>
			</tr>
			<tr>
				<td>CPU</td>
				<td>${telefon.specs.cpu}</td>
			</tr>
			<tr>
				<td>Memorija</td>
				<td>${telefon.specs.memorija}</td>
			</tr>
			<tr>
				<td>Baterija</td>
				<td>${telefon.specs.baterija}</td>
			</tr>
			<tr>
				<td>Boje</td>
				<td>${telefon.specs.boje}</td>
			</tr>
			</tbody>
		`)

		$("#komentarisi").submit(async function (event) {
			event.preventDefault()
			var form = $("#komentarisi")
			var ocena = -1
			var ime = form[0][5].value
			var kom = form[0][6].value
			for (i = 0; i < 5; i++) {
				if (form[0][i].checked) {
					ocena = i + 1
					break
				}
			}
			if (ocena == -1) {
				alert("Ocena nije uneta")
				return
			}
			if (ime == "") {
				alert("Nadimak nije unet")
				return
			}
			if (kom == "") {
				alert("Komentar je prazan")
				return
			}

			await fetch("http://localhost:9999/rectel/" + telefon._id + "/dodajkomentar/", {
				method: "POST",
				headers: {
					"Accept": "application/json",
					"Content-Type": "application/json"
				},
				body: JSON.stringify({
					"nadimak": ime,
					"komentar": kom,
					"ocena": ocena
				})
			})
			location.reload()
		})

		$("#najava").text(`
            Komentari (${telefon.komentari.length}): 
		`)
		const sortkomentari = telefon.komentari.sort((a, b) => (a.lajkovi + a.dislajkovi < b.lajkovi + b.dislajkovi) ? 1 : -1)
		$.each(sortkomentari, function (id, kom) {
			for (var i = 0; i < kom.ocena; i++) {
				$("#komentari").append(`
					<img src="star.png" alt="star"/>
				`)
			}
			$("#komentari").append(`
				<br/>
				
				<strong>${kom.nadimak}</strong>
				<br/>
				
				${kom.komentar}
				<br/>
				
				<button class="button btn btn-primary likebtn" id="${kom._id}"><img src="plus.png" alt="plus1"/> (${kom.lajkovi})</button>
				<button class="button btn btn-primary dislikebtn" id="${kom._id}"><img src="minus.png" alt="minus1"/> (${kom.dislajkovi})</button>
				<input type="button" class="btn btn-success replybtn" id="${kom._id}" value="Odgovori"/>
				<br/>
			`)

			const sortodgovori = kom.odgovori.sort((a, b) => (a.lajkovi + a.dislajkovi < b.lajkovi + b.dislajkovi) ? 1 : -1)
			$.each(sortodgovori, function (id, odg) {
				$("#komentari").append(`
				<div class="reply">
				<br/>
				
				<strong>${odg.nadimak} -> ${kom.nadimak}</strong>
				<br/>
				
				${odg.komentar}
				<br/>
				<button class="button btn btn-primary likebtnodg" id="${kom._id}/${odg._id}"><img src="plus.png" alt="plus1"/> (${odg.lajkovi})</button>
				<button class="button btn btn-primary dislikebtnodg" id="${kom._id}/${odg._id}"><img src="minus.png" alt="minus1"/> (${odg.dislajkovi})</button>
				<br/>
				</div>
				`)
			})

			$("#komentari").append(`
				<hr/>
			`)
		})

		$("#komentari").on("click", ".likebtn", function () {
			fetch("http://localhost:9999/rectel/" + telefon._id + "/" + this.id + "/dodajlike/", {
				method: "POST"
			})
			location.reload()
		})
		$("#komentari").on("click", ".dislikebtn", function () {
			fetch("http://localhost:9999/rectel/" + telefon._id + "/" + this.id + "/dodajdislike/", {
				method: "POST"
			})
			location.reload()
		})
		$("#komentari").on("click", ".replybtn", function () {
			var form = $("#komentarisi")
			var ime = form[0][5].value
			var kom = form[0][6].value
			if (ime == "") {
				alert("Nadimak nije unet")
				return
			}
			if (kom == "") {
				alert("Komentar je prazan")
				return
			}

			fetch("http://localhost:9999/rectel/" + telefon._id + "/" + this.id + "/dodajkomentar/", {
				method: "POST",
				headers: {
					"Accept": "application/json",
					"Content-Type": "application/json"
				},
				body: JSON.stringify({
					"nadimak": ime,
					"komentar": kom,
				})
			})

			location.reload()
		})
		$("#komentari").on("click", ".likebtnodg", function () {
			fetch("http://localhost:9999/rectel/" + telefon._id + "/" + this.id + "/dodajlike/", {
				method: "POST"
			})
			location.reload()
		})
		$("#komentari").on("click", ".dislikebtnodg", function () {
			fetch("http://localhost:9999/rectel/" + telefon._id + "/" + this.id + "/dodajdislike/", {
				method: "POST"
			})
			location.reload()
		})

		$("#komentari").wrap('<div class="comment"></div>');
		if (telefon.komentari.length == 0) {
			$("#komentari").html(`
                <h3>Nema komentara! :(</h3>
			`)
		}
	} else {
		$.each(listaTelefona, function (id, telefon) {
			$("#kontejner").append(`
				<div class="col-sm-4">
					<h3>${telefon.ime}</h3>
					<p>Cena: ${telefon.specs.cena}<br/>
					</p>
					<a href="telefon.html?idtel=${telefon._id}"><img src="${telefon.slika}" class="phone" alt="${telefon.kratkoime}"/></a>
				</div>
			`)
		})
	}
}



$(document).ready(async function () {
	listaTelefona = await (await fetch("http://localhost:9999/rectel/")).json()
	var params = new URLSearchParams(location.search)
	var odabir = listaTelefona.find(t => t._id == params.get("idtel"))
	ucitaj(odabir)
})