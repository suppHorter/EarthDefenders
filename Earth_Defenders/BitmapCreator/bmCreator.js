var bmWidth = 50;
var bmHeight = 50;

var mode = '';
var modeErase = 'erase';
var modeDraw = 'draw';

var bitMapOutput = [];

function getFieldAttributes(color = 'white') {
	var attributes = 'width: 5px;' + 
	'height: 5px;' + 
	'background-color:' + color + ';' +
	'border-style: solid;' +
	'border-width: 1px;';
	return attributes;
}

function initTable() {
	let table = document.getElementById('bmTable');
	console.log(table);
	for (let i=0;i<bmWidth; i++) {
	let tr = document.createElement('tr');
	let bmRow = [];
		for (let j=0;j<bmHeight; j++) {
			bmRow.push(0);
			let td = document.createElement('td');
			td.setAttribute('style',getFieldAttributes());
			td.id = i+ '' +j;
			td.onmouseover = function() {
				setActive(i,j);
			};
			bitMapOutput.push(bmRow);
			tr.append(td);
		}
	table.appendChild(tr);
	}
}

function setActive(x, y) {
	var clickedField = document.getElementById(x + '' + y);
	if (mode == modeDraw) {
	bitMapOutput[x][y] = 1;
	clickedField.setAttribute('style', getFieldAttributes('black'));
	}
	if (mode == modeErase) {
	bitMapOutput[x][y] = 0;
	clickedField.setAttribute('style', getFieldAttributes());
	}
}

function getBitmapArray() {
	console.table(bitMapOutput);
	// TODO:
}



function logKey(e) {
	if (e.code == 'KeyD') { //Draw
		mode = modeDraw;
	}
	if (e.code == 'KeyE') { //Erase
		mode = modeErase;
	}
}

document.addEventListener('keydown', logKey);

initTable();