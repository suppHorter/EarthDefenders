var bmWidth = 10;
var bmHeight = 10;

var mode = '';
var modeErase = 'erase';
var modeDraw = 'draw';

var bitMapOutput = [];
var bitMapInput = [];

function getFieldAttributes(color = 'white') {
	var attributes = 'width: 15px;' + 
	'height: 20px;' + 
	'background-color:' + color + ';' +
	'border-style: solid;' +
	'border-width: 1px;';
	return attributes;
}

function initTable() {
	let table = document.getElementById('bmTable');
	for (let i=0;i<bmWidth; i++) {
	let tr = document.createElement('tr');
	let bmRow = [];
		for (let j=0;j<bmHeight; j++) {
			let td = document.createElement('td');
			td.setAttribute('style',getFieldAttributes());
			td.id = i+ '|' +j;
			td.onmouseover = function() {
				setActive(i,j);
			};
			bmRow.push(0);
			tr.append(td);
		}
		bitMapOutput.push(bmRow);
		table.appendChild(tr);
	}
}

function showBitmapData() {
	var input = JSON.parse("[" + document.getElementById('inputData').value.toString() + "]");
	var widthInputBitmap = document.getElementById('bound_Y').value;
	var heightInputBitmap = document.getElementById('bound_X').value;
	
	let table = document.getElementById('showTable');
	console.log(input);
	
	let dataIndex = 0;
	let arrayInHex = [];
	for (let i=0;i<widthInputBitmap; i++) {
	let tr = document.createElement('tr');
		for (let j=0;j<heightInputBitmap; j++) {
			let td = document.createElement('td');
			
			if (input[dataIndex] == 1) {
				td.setAttribute('style',getFieldAttributes('black'));
			} else {
				td.setAttribute('style',getFieldAttributes());
			}
			td.id = i+ '|' +j;
			dataIndex++;
			tr.append(td);
		}
		table.appendChild(tr);
	}
	
	
	let tempByte = 0;
	let tempBitPower = 128;
	let bitMapEven = 0;
	for (let i=0; i < input.length; i++) {
		if (input[i] == 1) {
			tempByte += tempBitPower;
		}
		tempBitPower = parseInt(tempBitPower/2);
		
		console.log(i%8);
		bitMapEven = false;
		if (i%8 == 0 && i > 0) 
		{		
			arrayInHex.push(tempByte);
			bitMapEven = true;
			tempBitPower = 128;
			tempByte = 0;	
		}
	}
	
	if (bitMapEven) {	
		arrayInHex.push(tempByte);
	}
	
	console.log(arrayInHex);
	document.getElementById('toHex').value = arrayInHex;
}


function setActive(x, y) {
	var clickedField = document.getElementById(x + '|' + y);
	if (mode == modeDraw) {
		// window.document.getElementById('currentMode').innerHTML = modeDraw;
		bitMapOutput[x][y] = 1;
		clickedField.setAttribute('style', getFieldAttributes('black'));
	}
	if (mode == modeErase) {
		// window.document.getElementById('currentMode').innerHTML = modeErase;
		bitMapOutput[x][y] = 0;
		clickedField.setAttribute('style', getFieldAttributes());
	}
}

function getBitmapArray() {
	console.log("array[" + bmHeight + "][" + bmWidth + "] = {" + bitMapOutput.toString() + "}");
	// TODO:
}


function logKey(e) {
	if (e.code == 'KeyD') { //Draw
		mode = modeDraw;
	}
	if (e.code == 'KeyE') { //Erase
		mode = modeErase;
	}
	if (e.code == 'KeyL') { //Lock
		mode = '';
	}
}

document.addEventListener('keydown', logKey);

initTable();