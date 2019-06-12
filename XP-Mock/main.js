
function addEvent(){
    var event = Array.from($("#add-event").serializeArray())
    console.log(event)
    axios.post(URL +'/scheduler',arrayToObject(event )).then(r=>insertTable(r.data))

}

const arrayToObject = (array) =>
    array.reduce((obj, item) => {
        obj[item.name] = item.value
        return obj
    }, {})


function insertTable(arr, crTabFun) {
    const events = document.getElementById("events");
    events.innerHTML = ""
    arr.map(res=> {
        return {
            thing: res.thing,
            pin: res.pin,
            date: moment(res.date, 'DD-MM-YYYY'),
            action: res.action
        }
    })
        .sort((a,b)=>a.date.valueOf()- b.date.valueOf())
        .forEach((item,index)=>events.appendChild(crTabFun(item.thing,item.pin,item.date,item.action,index)))
};



const makeAction = (pin)=>[
    axios.get(URL +'/scheduler/pin').then(r=>console.log(r))
]



