function InitializeMain(){
    let Header = document.getElementById("Header");
    Header.style.transform = 'scale(1)';
    Header.style.opacity = '1';
    UpdateBalance();
}
function AddExpense(){
    let expense = document.querySelector("#ExpenseValue").value;
    localStorage.setItem("Balance", expense);
    UpdateBalance();
}

function UpdateBalance(){
    let Balance = localStorage.getItem("Balance");
    let BalanceValue = document.getElementById("Balance");
    BalanceValue.textContent = "Total Balance: " + Balance;
}