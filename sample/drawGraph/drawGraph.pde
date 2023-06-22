import grafica.*;
import jp.go.aist.rtm.OpenRTMUtil;
import jp.go.aist.rtm.RTC.port.InPort;
import jp.go.aist.rtm.RTC.util.DataRef;
import RTC.TimedPose2D;
import RTC.Pose2D;
import RTC.Point2D;
import RTC.Time;

//データ、InPortの変数を宣言
DataRef<TimedPose2D> indata;
InPort<TimedPose2D> inport;

//グラフに描画する点のデータを格納する配列を宣言
GPointsArray data;

public void setup() {
  //ウィンドウサイズを設定
  size(300, 300);

  //RTCを"drawGraph"というインスタンス名で生成
  OpenRTMUtil util = new OpenRTMUtil();
  util.createComponent("drawGraph");
  //データの初期化
  TimedPose2D val = new TimedPose2D();
  val.tm = new Time();
  val.data = new Pose2D();
  val.data.position = new Point2D();
  indata = new DataRef<TimedPose2D>(val);
  //InPortを"pose"という名前で生成
  inport = util.addInPort("pose", indata);

  //配列dataの初期化
  data = new GPointsArray();
}

int count = 0;
public void draw() {

  //InPortでデータを受信した時の処理
  if (inport.isNew())
  {
    //受信データの読み込み
    inport.read();
    //配列dataに取得した位置を追加する
    data.add((float)indata.v.data.position.x, (float)indata.v.data.position.y);

    //配列の大きさが1000を超えた場合、古いデータは捨てる
    if (data.getNPoints() > 1000)
    {
      data.remove(0);
    }
  }
  //グラフをウィンドウの(0,0)から(300,300)の範囲に描画する
  GPlot plot = new GPlot(this, 0, 0, 300, 300);
  //グラフの縦軸、横軸の上限、下限を設定する
  plot.setXLim(-1.0, 1.0);
  plot.setYLim(-1.0, 1.0);
  plot.setFixedXLim(true);
  plot.setFixedYLim(true);
  //配列dataをグラフに設定する
  plot.addPoints(data);
  //グラフの描画を開始する
  plot.beginDraw();
  //グラフに外枠、座標、折れ線、縦軸、横軸を描画する
  plot.drawBox();
  plot.drawPoints();
  plot.drawLines();
  plot.drawXAxis();
  plot.drawYAxis();
  //グラフの描画を終了する
  plot.endDraw();
}
