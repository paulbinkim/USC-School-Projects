// DATAPREV
// DATACURRENT
// DATAOPERATION
// DATANUMBER
// DATACLEAR
// DATAEQUALS

// Selecting Data From Buttons
const number = document.querySelectorAll('[DATANUMBER]')
const operation = document.querySelectorAll('[DATAOPERATION]')
const equals = document.querySelector('[DATAEQUALS]')
const clear = document.querySelector('[DATACLEAR]')
const PrevText = document.querySelector('[DATAPREV]')
const CurrText = document.querySelector('[DATACURRENT]')

// Creating Calculator Class to Store Information
class Calculator {
  constructor(PrevText, CurrText) {
    this.PrevText = PrevText
    this.CurrText = CurrText
    this.clear()
  }
	// Function to clear data
  clear() {
    this.CurrValue = ''
    this.PrevValue = ''
    this.operation = undefined
    this.oldValue = ''
    this.statement = false;
  }
	// Function to add on a number (string)
  appendNumber(number) {
    if (number === '.' && this.CurrValue.includes('.')) {
		return
	}
    this.CurrValue = this.CurrValue.toString() + number.toString()
  }
	// Funciton that allows you to choose/save operation picked
  chooseOperation(operation) {
	// We can check if the user inputted the 2nd value, if he/she didn't we do not allow them to pick new operation (input validation)'
    if (this.CurrValue === '') {
		return
	}
    if (this.PrevValue !== '') {
      this.compute()
    }
    this.operation = operation
    this.PrevValue = this.CurrValue
    this.CurrValue = ''
  }
	// Function to compute
  compute() {
    let computation
    const prev = parseFloat(this.PrevValue)
    const current = parseFloat(this.CurrValue)
    if (isNaN(prev) || isNaN(current)) {
		return
	}
    if (this.operation == '+') {
		computation = prev + current
	}
	else if (this.operation == '-') {
		computation = prev - current
	}
	else if (this.operation == '*') {
		computation = prev * current
	}
	else if (this.operation == '/') {
		computation = prev / current
	}
	else {
		return
	}
	this.oldValue = this.CurrValue
    this.CurrValue = computation
    this.statement = true;
    

    
  }
	// Returns number
  getDisplayNumber(number) {
    const stringNumber = number.toString()
    const integerDigits = parseFloat(stringNumber.split('.')[0])
    const decimalDigits = stringNumber.split('.')[1]
    let integerDisplay
    if (isNaN(integerDigits)) {
      integerDisplay = ''
    } 
    else {
      integerDisplay = integerDigits.toLocaleString('en', { maximumFractionDigits: 0 })
    }
    if (decimalDigits != null) {
      return `${integerDisplay}.${decimalDigits}`
    } 
    else {
      return integerDisplay
    }
  }
	// Update Display on Calculator
  updateDisplay() {
    this.CurrText.innerText =
      this.getDisplayNumber(this.CurrValue)
    if (this.operation != null && this.statement == false) {
      this.PrevText.innerText = `${this.getDisplayNumber(this.PrevValue)} ${ this.operation} ${this.oldValue}`
    } 
    else if (this.operation != null && this.statement == true) {
		this.PrevText.innerText = `${this.getDisplayNumber(this.PrevValue)} ${ this.operation} ${this.oldValue} ${"="}`
	}
    else {
      this.PrevText.innerText = ''
    }
  }
}
	
// Creating Calculator Object
const calculator = new Calculator(PrevText, CurrText)

// Event Handlers
number.forEach(button => {
  button.addEventListener('click', () => {
    calculator.appendNumber(button.innerText)
    calculator.updateDisplay()
  })
})

operation.forEach(button => {
  button.addEventListener('click', () => {
    calculator.chooseOperation(button.innerText)
    calculator.updateDisplay()
  })
})

equals.addEventListener('click', button => {
  calculator.compute()
  calculator.updateDisplay()
})

clear.addEventListener('click', button => {
  calculator.clear()
  calculator.updateDisplay()
})
