const express = require("express")
const mongoose = require("mongoose")
const express1 = express()
const telefoni = require("./telefoni")
const port = 9999

const router = express.Router()

async function getTelefon(req, res, next) {
    try {
        let telefon = await telefoni.findById(req.params.idtel)
        if (telefon == undefined) {
            return res.status(404).json({ message: "Nema telefona sa tim id" })
        }
        res.telefon = telefon
        next()
    } catch (err) {
        return res.status(500).json({ message: err.message })
    }
}

// dobij sve telefone
router.get("/", async (req, res) => {
    res.json(await telefoni.find())
})

// dobij telefon
router.get("/:idtel/", getTelefon, async (req, res) => {
    try {
        res.json(res.telefon)
        res.sendStatus(200)
    } catch (err) {
        res.status(500).json({ message: err.message })
    }
})

// dodaj komentar
router.post("/:idtel/dodajkomentar/", async (req, res) => {
    try {
        const telefon = await telefoni.findById(req.params.idtel)
        const komentar = {
            _id: new mongoose.Types.ObjectId(),
            nadimak: req.body.nadimak,
            komentar: req.body.komentar,
            ocena: req.body.ocena,
            lajkovi: 0,
            dislajkovi: 0,
            odgovori: []
        }
        telefon.komentari.push(komentar)
        await telefon.save()
        res.sendStatus(200)
    } catch (err) {
        return res.status(500).json({ message: err.message })
    }
})

// like za komentar
router.post("/:idtel/:idkom/dodajlike/", async (req, res) => {
    try {
        const telefon = await telefoni.findById(req.params.idtel)
        const komentar = telefon.komentari.find(k => req.params.idkom == k._id)
        komentar.lajkovi++;
        await telefon.save()
        res.sendStatus(200)
    } catch (err) {
        return res.status(500).json({ message: err.message })
    }
})

// dislike za komentar
router.post("/:idtel/:idkom/dodajdislike/", async (req, res) => {
    try {
        const telefon = await telefoni.findById(req.params.idtel)
        const komentar = telefon.komentari.find(k => req.params.idkom == k._id)
        komentar.dislajkovi++;
        await telefon.save()
        res.sendStatus(200)
    } catch (err) {
        return res.status(500).json({ message: err.message })
    }
})

// obrisi komentar
router.delete("/:idtel/:idkom/obrisikomentar/", async (req, res) => {
    try {
        const telefon = await telefoni.findById(req.params.idtel)
        telefon.komentari.find(k => req.params.idkom == k._id).remove()
        await telefon.save()
        res.sendStatus(200)
    } catch (err) {
        return res.status(500).json({ message: err.message })
    }
})

// dodaj odgovor na komentar
router.post("/:idtel/:idkom/dodajkomentar/", async (req, res) => {
    try {
        const telefon = await telefoni.findById(req.params.idtel)
        const komentar = telefon.komentari.find(k => req.params.idkom == k._id)
        const odgovor = {
            _id: new mongoose.Types.ObjectId(),
            nadimak: req.body.nadimak,
            komentar: req.body.komentar,
            lajkovi: 0,
            dislajkovi: 0
        }
        komentar.odgovori.push(odgovor)
        await telefon.save()
        res.sendStatus(200)
    } catch (err) {
        return res.status(500).json({ message: err.message })
    }
})

// like za odgovor komentara
router.post("/:idtel/:idkom/:idodg/dodajlike/", async (req, res) => {
    try {
        const telefon = await telefoni.findById(req.params.idtel)
        const komentar = telefon.komentari.find(k => req.params.idkom == k._id)
        const odgovor = komentar.odgovori.find(o => req.params.idodg == o._id)
        odgovor.lajkovi++;
        await telefon.save()
        res.sendStatus(200)
    } catch (err) {
        return res.status(500).json({ message: err.message })
    }
})

// dislike za odgovor komentara
router.post("/:idtel/:idkom/:idodg/dodajdislike/", async (req, res) => {
    try {
        const telefon = await telefoni.findById(req.params.idtel)
        const komentar = telefon.komentari.find(k => req.params.idkom == k._id)
        const odgovor = komentar.odgovori.find(o => req.params.idodg == o._id)
        odgovor.dislajkovi++;
        await telefon.save()
        res.sendStatus(200)
    } catch (err) {
        return res.status(500).json({ message: err.message })
    }
})

mongoose.connection.once("open", () => console.log("Baza telefona se otvorila"))
mongoose.connect("mongodb://localhost/rectel", { useNewUrlParser: true, useUnifiedTopology: true })
express1.use(express.json())
express1.use(function (req, res, next) {
    res.setHeader("Access-Control-Allow-Origin", "*");
    res.setHeader("Access-Control-Allow-Credentials", "true");
    res.setHeader("Access-Control-Allow-Methods", "GET,HEAD,OPTIONS,POST,PUT");
    res.setHeader("Access-Control-Allow-Headers", "Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Access-Control-Request-Headers");
    next();
})
express1.use("/rectel", router).listen(port)
