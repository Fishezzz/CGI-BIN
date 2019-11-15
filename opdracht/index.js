fetch('./data.json')
    .then(response => {
        return response.json();
    })
    .then(result => {
        // Work with JSON data here
        console.log(result);
        fillTable(result);
    })
    .catch(err => {
        console.log('Error: ' + err);
    })

function fillTable(data) {
    data.forEach(entry => {
        var tr = document.createElement('tr');
        var td = document.createElement('td');
        td.innerHTML = entry.name;
        tr.appendChild(td);
        var td = document.createElement('td');
        td.innerHTML = entry.age;
        tr.appendChild(td);
        var td = document.createElement('td');
        td.innerHTML = getTimeString(entry.timestamp);
        tr.appendChild(td);
        document.getElementById("dataTable").appendChild(tr);
    });
}

function getTimeString(time) {
    var date = new Date(time * 1000);
    var year = date.getFullYear();
    var month = "0" + date.getMonth();
    var day = "0" + date.getDay();
    var hours = "0" + date.getHours();
    var minutes = "0" + date.getMinutes();
    var seconds = "0" + date.getSeconds();

    var formattedTime = `${year}-${month.substr(-2)}-${day.substr(-2)} T ${hours.substr(-2)}:${minutes.substr(-2)}:${seconds.substr(-2)}`;

    return formattedTime;
}