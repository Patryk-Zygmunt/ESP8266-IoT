
function addEvent(){
    var event = Array.from($("#add-event").serializeArray())
    axios.post(URL +'/scheduler',arrayToObject(event )).then(r=>insertTable(r.data))

}

const arrayToObject = (array) =>
    array.reduce((obj, item) => {
        obj[item.name] = item.value
        return obj
    }, {})


function insertTable(arr) {
    const events = document.getElementById("events");
    events.innerHTML = ""
    arr.map(res=> {
        return {
            thing: res.thing,
            pin: res.pin,
            date: moment(res.date, 'DD-MM-YYYY')
        }
    })
        .sort((a,b)=>a.date.valueOf()- b.date.valueOf())
        .forEach((item,index)=>events.appendChild(createTableRow(item.thing,item.pin,item.date,index)))
};



const deleteEvent = (name,date)=>[

    axios.delete(URL +'/scheduler',arrayToObject(event )).then(r=>insertTable(r.data))
]

function createTableRow(name,pin,date,index) {
    var frag = document.createDocumentFragment(),
        temp = document.createElement('tr');
    temp.innerHTML =
        `<th scope='row'>${index}</th>
            <td>${name}</td>
            <td>${pin}</td>
            <td>${date.format('DD-MM-YYYY').toLocaleString()}</td>
            <td><button type="button" class="btn btn-danger" onclick="deleteEvent('${name}','${pin}')">Delete</button></td>
`
    frag.appendChild(temp)
    return frag;
}

