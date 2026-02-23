object GradeAnalyzer {

def main(args: Array[String]): Unit = {

    val rawScores = List(78, 90, 66, 45, 88, 92, 55, 73, 60, 100)

    val adjusted = adjustScores(rawScores)
    val filtered = filterPassed(adjusted, 60)
    val avg      = average(filtered)
    val stats    = minMax(filtered)
    val freq     = frequencyMap(filtered)

    println(s"Original: $rawScores")
    println(s"Adjusted: $adjusted")
    println(s"Passed:   $filtered")
    println(s"Average:  $avg")
    println(s"Min/Max:  $stats")
    println(s"Frequency:$freq")

    println("Grades classification:")
    for (score <- filtered) {                     // <-
      println(s"$score -> ${classify(score)}")    // ->
    }

    val range1 = 1 to 5
    val range2 = 1 until 5
    println(s"Range1 sum: ${range1.sum}")
    println(s"Range2 product: ${range2.product}")

    val anyValue: Any = avg
    if (anyValue.isInstanceOf[Double]) {
      val d = anyValue.asInstanceOf[Double]
      println(s"Avg as Double: ${d + 0.0}")
    }

    val evenOdd: PartialFunction[Int,String] = {
      case x if x % 2 == 0 => "even"
      case _               => "odd"
    }
    println("Parity test:")
    filtered.foreach(x => println(s"$x is ${evenOdd(x)}")) // =>
  }

  def adjustScores(scores: List[Int]): List[Int] = {
    var result = scores
    result = 0 +: result               // +:
    result = result :+ 50              // :+
    result = result ++ List(75)        // ++
    result = result -- List(45)        // --
    result = 100 :: result             // ::
    result.map(x => if (x > 100) 100 else if (x < 0) 0 else x)
  }

  def filterPassed(scores: List[Int], threshold: Int): List[Int] = {
    scores.filter(x => (x >= threshold) && !(x < 0))
  }

  def average(scores: List[Int]): Double = {
    var sum = 0
    for (s <- scores) {                // <-
      sum += s                         // +=
    }
    if (scores.nonEmpty) sum.toDouble / scores.length else 0.0
  }

  def minMax(scores: List[Int]): (Int, Int) = {
    var min = Int.MaxValue
    var max = Int.MinValue

    for (s <- scores) {
      if (s < min) min = s
      if (s > max) max = s
    }
    (min, max)
  }

  def frequencyMap(scores: List[Int]): Map[Int, Int] = {
    var freq = Map[Int, Int]()
    for (s <- scores) {
      val current = if (freq.contains(s)) freq(s) else 0
      freq += (s -> (current + 1))      // -> и +=
    }
    freq
  }

  def classify(score: Int): String = {
    score match {                       // match/case
      case s if s >= 90 => "Excellent"
      case s if s >= 75 => "Good"
      case s if s >= 60 => "Pass"
      case _            => "Fail"
    }
  }

  // Демонстрация побитовых и сдвигов в осмысленном виде
  def bitwiseDemo(x: Int): Int = {
    val shifted = (x << 1) >> 1
    val masked  = shifted & 0xFF
    val toggled = masked ^ 0x0F
    ~toggled
  }

}