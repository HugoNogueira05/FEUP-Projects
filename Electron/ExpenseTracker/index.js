let transactionHist = "";
let symbol = "€";
function InitializeMain(){
    let Header = document.getElementById("Header");
    Header.style.transform = 'scale(1)';
    Header.style.opacity = '1';
    if (localStorage.getItem("Balance") == null){
        localStorage.setItem("Balance", 0);
    }
    UpdateBalance();
    displayBalance();
    
    transactionHist = localStorage.getItem("TransactionHist");
    if (transactionHist && transactionHist.length > 0){
        let transactions = transactionHist.split("_"); 
         // Iterate over the transactions array to process each value
        for (let i = 1; i < transactions.length; i+=4) {
            AddToHistory(transactions[i], transactions[i+1], transactions[i+2], transactions[i+3]);
        }
    }
    else{
        transactionHist = "";
        console.log("No History");
    }
}
function AddIncome(){
    let income = document.querySelector("#IncomeValue").value;
    if (income != ""){
        localStorage.setItem("Balance" , parseFloat(localStorage.getItem("Balance")) + parseFloat(income));
        UpdateBalance();
        AddToHistory(income, 0, "Income", new Date().getDate() + "/" + (parseInt(new Date().getMonth()) + 1) + "/" + new Date().getFullYear());
        transactionHist += "_" + income + "_" + 0 + "_" + "Income" + "_" + new Date().getDate() + "/" + (new Date().getMonth() + 1) + "/" + new Date().getFullYear();
        localStorage.setItem("TransactionHist" , transactionHist);
    }
}
function AddExpense(){
    let expense = document.querySelector("#ExpenseValue").value;
    if (expense != ""){
        localStorage.setItem("Balance" , parseFloat(localStorage.getItem("Balance")) - parseFloat(expense));
        UpdateBalance();
        AddToHistory(expense, 1, "description", new Date().getDate() + "/" + (parseInt(new Date().getMonth()) + 1) + "/" + new Date().getFullYear());
        transactionHist += "_" + expense + "_" +  1 + "_" +  "description" + "_" +   new Date().getDate() + "/" + (parseInt(new Date().getMonth()) + 1) + "/" + new Date().getFullYear();
        localStorage.setItem("TransactionHist" , transactionHist);
    }
}

function UpdateBalance(){
    let Balance = localStorage.getItem("Balance");
    let BalanceValue = document.getElementById("Balance");
    BalanceValue.textContent = Balance + " " + symbol;
}

function ClearBalance(){
    localStorage.setItem("Balance" ,0);
    UpdateBalance();
}


function displayBalance(){
    ClearDisplay();
    document.getElementById("BalanceTab").style.display = 'flex';
}

function ChangeShape(){
    let SideBar = document.getElementById("Sidebar");
    let SideBarBtn = document.getElementById("SideBarButton");
    let BalanceText = document.getElementById("BalanceSelector");
    let HistoryText = document.getElementById("HistorySelector");
    if (SideBar.style.width == '0px'){
        SideBar.style.width = '30vh';
        SideBarBtn.style.transform = 'rotate(180deg)';
        BalanceText.style.opacity= '1';
        HistoryText.style.opacity= '1';
    }
    else{
        SideBar.style.width = '0px';
        SideBarBtn.style.transform = 'rotate(0deg)';
        BalanceText.style.opacity= '0';
        HistoryText.style.opacity= '0';
    }
}

function displayHistory(){
    ClearDisplay();
    document.getElementById("HistoryTab").style.display = 'flex';
}

function ClearDisplay(){
    document.getElementById("BalanceTab").style.display = 'none';
    document.getElementById("HistoryTab").style.display = 'none';
}

function AddToHistory(value, type, description, date) {
    let transactionList = document.getElementById("TransactionList");
    let row = transactionList.insertRow(-1); // Insert a row at the end of the table
    let valueCell = row.insertCell(0); // Insert a new cell for the value
    let dateCell = row.insertCell(1); // Insert a new cell for the date
    let descriptionCell = row.insertCell(2); // Insert a new cell for the description

    // Set the text for each cell
    descriptionCell.textContent = description;
    dateCell.textContent = date;

    // Set the color based on the transaction type
    if (type == 0) { // Income
        valueCell.textContent = "+" + value;
    } else { // Expense
        valueCell.textContent = "-" + value;
        row.style.color = 'red';
    }
}

function ClearHistory(){
    let transactionList = document.getElementById("TransactionList");
    while (transactionList.rows.length > 0) {
        transactionList.deleteRow(0);
    }
    localStorage.setItem("TransactionHist", "");	
}