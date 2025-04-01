// -*- Java -*-
// <rtc-template block="description">
/*!
 * @file  drawGraphImpl.java
 * @brief Draw graph component
 * @date  $Date$
 *
 * $Id$
 */
// </rtc-template>

import java.lang.reflect.Array;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import RTC.TimedPose2D;
import jp.go.aist.rtm.RTC.DataFlowComponentBase;
import jp.go.aist.rtm.RTC.Manager;
import jp.go.aist.rtm.RTC.port.InPort;
import jp.go.aist.rtm.RTC.util.DataRef;
import RTC.ReturnCode_t;

import grafica.*;

// <rtc-template block="component_description">
/**
 * drawGraphImpl
 * <p>
 * Draw graph component
 *
 */
// </rtc-template>
public class drawGraphImpl extends DataFlowComponentBase {

  /**
   * constructor
   * @param manager Manager Object
   */
    public drawGraphImpl(Manager manager) {  
        super(manager);
        // <rtc-template block="initializer">
        m_in_val = new TimedPose2D();
        initializeParam(m_in_val);
        m_in = new DataRef<TimedPose2D>(m_in_val);
        m_inIn = new InPort<TimedPose2D>("in", m_in);
        // </rtc-template>

    }

    /**
     *
     * The initialize action (on CREATED-&gt;ALIVE transition)
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
    @Override
    protected ReturnCode_t onInitialize() {
        // Registration: InPort/OutPort/Service
        // <rtc-template block="registration">
        // Set InPort buffers
        addInPort("in", m_inIn);
        // </rtc-template>

        return super.onInitialize();
    }

    /**
     *
     * The finalize action (on ALIVE-&gt;END transition)
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
//    @Override
//    protected ReturnCode_t onFinalize() {
//        return super.onFinalize();
//    }

    /**
     *
     * The startup action when ExecutionContext startup
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
//    @Override
//    protected ReturnCode_t onStartup(int ec_id) {
//        return super.onStartup(ec_id);
//    }

    /**
     *
     * The shutdown action when ExecutionContext stop
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
//    @Override
//    protected ReturnCode_t onShutdown(int ec_id) {
//        return super.onShutdown(ec_id);
//    }

    /**
     *
     * The activated action (Active state entry action)
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
    @Override
    protected ReturnCode_t onActivated(int ec_id) {
        //配列dataの初期化
        data = new GPointsArray();
        return super.onActivated(ec_id);
    }

    /**
     *
     * The deactivated action (Active state exit action)
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
//    @Override
//    protected ReturnCode_t onDeactivated(int ec_id) {
//        return super.onDeactivated(ec_id);
//    }

    /**
     *
     * The execution action that is invoked periodically
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
    @Override
    protected ReturnCode_t onExecute(int ec_id) {
        //InPortでデータを受信した時の処理
        if (m_inIn.isNew())
        {
          //受信データの読み込み
          m_inIn.read();
          //配列dataに取得した位置を追加する
          data.add((float)m_in.v.data.position.x, 
                   (float)m_in.v.data.position.y);
      
          //配列の大きさが1000を超えた場合、古いデータは捨てる
          if (data.getNPoints() > 1000)
          {
            data.remove(0);
          }
        }
        //グラフをウィンドウの(0,0)から(300,300)の範囲に描画する
        GPlot plot = new GPlot(m_applet, 0, 0, 300, 300);
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
        return super.onExecute(ec_id);
    }

    /**
     *
     * The aborting action when main logic error occurred.
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
//  @Override
//  public ReturnCode_t onAborting(int ec_id) {
//      return super.onAborting(ec_id);
//  }

    /**
     *
     * The error action in ERROR state
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
//    @Override
//    public ReturnCode_t onError(int ec_id) {
//        return super.onError(ec_id);
//    }

    /**
     *
     * The reset action that is invoked resetting
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
//    @Override
//    protected ReturnCode_t onReset(int ec_id) {
//        return super.onReset(ec_id);
//    }

    /**
     *
     * The state update action that is invoked after onExecute() action
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
//    @Override
//    protected ReturnCode_t onStateUpdate(int ec_id) {
//        return super.onStateUpdate(ec_id);
//    }

    /**
     *
     * The action that is invoked when execution context's rate is changed
     *
     * @param ec_id target ExecutionContext Id
     *
     * @return RTC::ReturnCode_t
     * 
     * 
     */
//    @Override
//    protected ReturnCode_t onRateChanged(int ec_id) {
//        return super.onRateChanged(ec_id);
//    }
//
    /**
     */

    /**
     */
    // DataInPort declaration
    // <rtc-template block="inport_declare">
    protected TimedPose2D m_in_val;
    protected DataRef<TimedPose2D> m_in;
    /*!
     * ロボットの現在位置
     * - Type: RTC::TimedPose2D
     * - Unit: m, rad
     */
    protected InPort<TimedPose2D> m_inIn;
    
    //グラフに描画する点のデータを格納する配列を宣言
    GPointsArray data; //追加

    
    // </rtc-template>

    // DataOutPort declaration
    // <rtc-template block="outport_declare">
    
    // </rtc-template>

    // CORBA Port declaration
    // <rtc-template block="corbaport_declare">
    
    // </rtc-template>

    // Service declaration
    // <rtc-template block="service_declare">
    
    // </rtc-template>

    // Consumer declaration
    // <rtc-template block="consumer_declare">
    
    // </rtc-template>


    private void initializeParam(Object target) {
        Class<?> targetClass = target.getClass();
        ClassLoader loader = target.getClass().getClassLoader();
        //
        Field[] fields = targetClass.getFields();
        for(Field field : fields) {
            if(field.getType().isPrimitive()) continue;
            
            try {
                if(field.getType().isArray()) {
                    Object arrayValue = null;
                    Class<?> clazz = null;
                    if(field.getType().getComponentType().isPrimitive()) {
                        clazz = field.getType().getComponentType();
                    } else {
                        clazz = loader.loadClass(field.getType().getComponentType().getName());
                    }
                    arrayValue = Array.newInstance(clazz, 0);
                    field.set(target, arrayValue);
                    
                } else {
                    Constructor<?>[] constList = field.getType().getConstructors();
                    if(constList.length==0) {
                        Method[] methodList = field.getType().getMethods();
                        for(Method method : methodList) {
                            if(method.getName().equals("from_int")==false) continue;
                            Object objFld = method.invoke(target, new Object[]{ new Integer(0) });
                            field.set(target, objFld);
                            break;
                        }
                        
                    } else {
                        Class<?> classFld = Class.forName(field.getType().getName(), true, loader);
                        Object objFld = classFld.newInstance();
                        initializeParam(objFld);
                        field.set(target, objFld);
                    }
                }
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            } catch (InstantiationException e) {
                e.printStackTrace();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            } catch (IllegalArgumentException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            }
        }
    }
    
    void setPApplet(PApplet applet)
    {
      m_applet = applet;
    }
    
    private PApplet m_applet;
}
