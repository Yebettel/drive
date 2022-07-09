const mongoose = require("mongoose")

const schema = mongoose.Schema({
    kratkoime: String,
    ime: String,
    punarecenzija: String,
    recenzija: String,
    slika: String,
    specs: {
        cena: String,
        kamera: String,
        mreza: String,
        datumobjave: String,
        ekran: String,
        os: String,
        cpu: String,
        memorija: String,
        baterija: String,
        boje: [String]
    },
    komentari: [{
        nadimak: String,
        komentar: String,
        ocena: Number,
        lajkovi: Number,
        dislajkovi: Number,
        odgovori: [{
            nadimak: String,
            komentar: String,
            lajkovi: Number,
            dislajkovi: Number
        }]
    }]
})

module.exports = mongoose.model("Model", schema, "telefoni")