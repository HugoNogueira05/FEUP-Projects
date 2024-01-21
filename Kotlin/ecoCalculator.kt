import java.text.DecimalFormat
fun main() {
    println("Welcome to the EcoCalculator!")
    println("Type 1 if your car runs on Gasoline, type 2 if your car runs on Diesel and type 3 if your car is electric:")
    val carType = readlnOrNull()
    println("Please choose the distance you want to travel in Km:")
    val distanceKm = readln().toInt()
    if (carType != "3"){
        println("Finally, what is the average consumption of your vehicle (___l/100km)?")
    }
    else{
        println("Finally, what is the average consumption of your vehicle (___Kw/100km)?")
    }
    val averageConsumption = readln().toFloat()
    val df = DecimalFormat("#.##")
    if (carType == "1") {
        val gasPrice = 1.862
        val fuelPollution = 2.300
        val moneySaved = df.format( savings(gasPrice, distanceKm , averageConsumption))
        println("If you were using an electric car you could have saved $moneySaved€.")
        val emissions = df.format(emissions(fuelPollution,distanceKm,averageConsumption))
        println("Your trip caused the emission of $emissions Kg of CO2.")
        println("You are not Eco-Friendly!!!")
    } else if (carType == "2") {
        val gasPrice = 1.812
        val fuelPollution = 2.700
        val moneySaved= df.format(savings(gasPrice, distanceKm, averageConsumption))
        println("If you were using an electric car you could have saved $moneySaved€.")
        val emissions = df.format(emissions(fuelPollution,distanceKm,averageConsumption))
        println("Your trip caused the emission of $emissions Kg of CO2.")
        println("You are not Eco-Friendly!!!")

    } else if (carType == "3") {
        println("Good Job! You are already Eco-Friendly!!!")
        val fuelPollution = 0.389
        val electricPrice = df.format(((distanceKm * averageConsumption)* 0.01)*0.15)
        println("In that trip you spent a total of $electricPrice€.")
        val emissions = df.format(fuelPollution * (distanceKm * averageConsumption)*0.01)
        println("Your trip caused the emission of $emissions Kg of CO2.")
    } else {
        print("Error, please choose one of the 3 options available")
    }
}

//calculate money
fun savings(gasPrice: Double, distanceKm: Int, averageConsumption: Float): Float {
    val fuelNeeded = (distanceKm*0.01)*averageConsumption
    val moneyNeeded = fuelNeeded * gasPrice
    val electricPrice = ((distanceKm *134)* 0.0025)*0.15
    val saved = (moneyNeeded - electricPrice).toFloat()
    return saved
}

//calculate emissions
fun emissions(fuelPollution: Double, distanceKm: Int, averageConsumption: Float): Double{
    val fuelNeeded = (distanceKm*0.01)*averageConsumption
    return fuelPollution * fuelNeeded
}
