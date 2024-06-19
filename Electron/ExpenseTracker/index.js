function InitializeMain(){
    let Header = document.getElementById("Header");
    Header.style.transform = 'scale(1)';
    Header.style.opacity = '1';
    if (localStorage.getItem("Balance") == null){
        localStorage.setItem("Balance", 0);
    }
    UpdateBalance();
    setInterval( displayBalance , 2000);
}
function AddIncome(){
    let income = document.querySelector("#IncomeValue").value;
    if (income != ""){
        localStorage.setItem("Balance" , parseFloat(localStorage.getItem("Balance")) + parseFloat(income));
        UpdateBalance();
    }
}
function AddExpense(){
    let expense = document.querySelector("#ExpenseValue").value;
    if (expense != ""){
        localStorage.setItem("Balance" , parseFloat(localStorage.getItem("Balance")) - parseFloat(expense));
        UpdateBalance();
    }
}

function UpdateBalance(){
    let Balance = localStorage.getItem("Balance");
    let BalanceValue = document.getElementById("Balance");
    BalanceValue.textContent = "Total Balance: " + Balance;
}

function ClearBalance(){
    localStorage.setItem("Balance" ,0);
    UpdateBalance();
}


function displayBalance(){
     document.getElementById("BalanceTab").style.display = 'flex';
}

function ChangeShape(){
    let SideBar = document.getElementById("SideBar");
    if (SideBar.style.width == '0px'){
        SideBar.style.width = '30vh';
    }
    else{
        SideBar.style.width = '0px';
    }
}