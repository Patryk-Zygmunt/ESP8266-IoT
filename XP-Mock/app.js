const express = require('express')
const bodyParser = require("body-parser");
const app = express()
var moment = require('moment');


app.use(bodyParser.urlencoded({
    extended: true
}));

app.use(bodyParser.json());

app.use(function (req, res, next) {

    // Website you wish to allow to connect
    res.setHeader('Access-Control-Allow-Origin', '*');

    // Request methods you wish to allow
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

    // Request headers you wish to allow
    res.setHeader('Access-Control-Allow-Headers', '*');

    // Set to true if you need the website to include cookies in the requests sent
    // to the API (e.g. in case you use sessions)
    res.setHeader('Access-Control-Allow-Credentials', true);

    // Pass to next layer of middleware
    next();
});

app.post('/scheduler/', (req, res) => {
    mock = {
        date : moment(req.body.date).format('DD-MM-YYYY'),
        pin: req.body.pin,
        thing : req.body.thing,
        action : req.body.action
    }
    mock2 = {
        date : new Date(),
        pin: 2,
        thing : "light in bedroom",
        action : "turn on"
    }
    res.send(200,[mock,mock2])
});

app.post('/action', (req, res) => {
    mock = {
        pin: req.body.pin,
        thing : req.body.thing
    }
    console.log("action",mock)
    if(req.body.thing ==="fail")res.send(400,mock);
    res.send(200,mock)
});

app.get('/scheduler/', (req, res) => {
    mock = {
        date : new Date(),
        pin: 12,
        thing : "gate",
        action : "turn on"
    }
    mock2 = {
        date : '23-12-24',
        pin: 2,
        thing : "light in bedroom",
        action: "turn off",
    }
    res.send([mock,mock2])
});



app.listen(3000, () => console.log('Example app listening on port 3000!'))
