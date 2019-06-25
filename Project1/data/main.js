
function addEvent() {
    var event = Array.from($("#add-event").serializeArray())
    console.log(event)
    axios.post('/scheduler', arrayToObject(event)).then(r => insertTable(r.data))

}

const arrayToObject = (array) =>
    array.reduce((obj, item) => {
        obj[item.name] = item.value
        return obj
    }, {})

function insertTable(arr) {
    const events = document.getElementById("events");
    events.innerHTML = ""
    arr.map(res => {
        return {
            thing: res.thing,
            pin: res.pin,
            date: moment(res.date, 'DD-MM-YYYY HH:mm'),
            action: res.action
        }
    })
        .sort((a, b) => a.date.valueOf() - b.date.valueOf())
        .forEach((item, index) => events.appendChild(createTableRow(item.thing, item.pin, item.date, item.action, index)))
};

function createTableRow(name, pin, d, action, index) {
    var frag = document.createDocumentFragment(),
        temp = document.createElement('tr');
    temp.innerHTML =
        `<th scope='row'>${index}</th>
            <td>${name}</td>
            <td>${pin}</td>
            <td>${(d.format('DD-MM-YYYY HH:mm')).toLocaleString()}</td>
            <td><button type="button" class="btn btn-secondary" onclick="deleteEvent('${name}','${pin}')">${action}</button></td>
    `
    frag.appendChild(temp)
    return frag;
}

const makeAction = (pin) => [
    axios.get('/scheduler/pin').then(r => console.log(r))
]


function uniqeArr(arr){
   let  pinArr = arr.map(i=>i.pin)
    return   arr.filter(function (item, pos) {
        return pinArr.indexOf(item.pin) == pos;
    })
}




