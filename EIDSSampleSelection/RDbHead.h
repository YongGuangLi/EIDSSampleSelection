/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: RDbHead.h
* 文件描述: 数据结构公共头文件
*  作  者 : 林晓雨，
* 创建日期: 2015-5-14 20:46:02
*******************************************************************************/

#ifndef __RDBHEAD_H__
#define __RDBHEAD_H__

///////////////////////////公共SQL/////////////////////////////////////
///////////////////////////ORACLE//////////////////////////////////////
const std::string g_strInsertVersionSQL =  
		"begin P_SYS_Update_VersionNumber(:v_service_name<char[100],in>,\
	   :v_version_no<char[100],in>,:v_logfile_path<char[100],in>,\
	   :v_result<char[20],out>);end;";

/////////////////////////////////样本筛选功能////////////////////////////////
/////////////////////////////////ORACLE///////////////////////////////////////
//检测数据库连接
const std::string g_strIsConnectSQL = "select 1 from dual";

//获取关系数据库当前时间
const std::string g_strRdbSysDateSQL =
		"select to_char(sysdate,'yyyy-mm-dd hh24:mi:ss') today from dual";

//获取数据库唯一key
const std::string g_strSysGuidSQL = 
		"select RAWTOHEX(sys_guid()) id from dual";

//查询模型状态与时间段
const std::string g_strModelSampleTimeSQL = 
        "select model_id, id,  start_time,end_time,step from tb_eids_model_sample_time t  where t.state = 1 or t.state = 4";

//查询模型状态与时间段(按机组分步式部署)
const std::string g_strModelSampleTimeDistributedSQL = 
        "select s1.model_id, s1.id, s1.start_time, s1.end_time, s1.step from tb_eids_model_sample_time s1, tb_eids_model s2\
        where (s1.state = 1 or s1.state = 4) and (s1.model_id = s2.id and s2.set_id in (%s))";
  
//查询样本时间段过滤条件(手动筛选)
const std::string g_strSampleTimeConSQL = 
		//LINXIAOY,修正bug
		//"select t2.point_id, t1.upper_limit_cond, t1.upper_limit_value, \
		//t1.lower_limit_cond, t1.lower_limit_value \
		//from tb_eids_model_sample_time_con t1, tb_eids_model_monit_point t2 \
		//where t1.monit_point_id = t2.id and sample_time_id = '%s'";

		"select monit_point_id, upper_limit_cond, upper_limit_value,\
		lower_limit_cond,lower_limit_value from tb_eids_model_sample_time_con\
		where sample_time_id = '%s'";

//模型监测条件(模式筛选)
const std::string g_strModelConditionSQL = 
        "select id, name, local_var, concat(out_var,out_var_func), expression  \
		from tb_eids_model_condition where model_id = '%s'";

//查询模型测点
const std::string g_strMonitPointSQL = 
        "select point_code, SOURCE_ID_ORIGINAL from tb_pub_point";

//诊断模型样本时间段
const std::string g_strInsertModelSampleTimeSQL = 
		"insert into tb_eids_model_sample_time(id, start_time, end_time, \
         step, model_id, model_condition_id, samples_sum, state) values('%1', \
         str_to_date('%2','%Y-%m-%d %H:%i:%s'), str_to_date('%3','%Y-%m-%d %H:%i:%s'),	\
         %4,  '%5', '%6', %7 , '%8')" ;

//诊断模型样本时间段手工筛选条件
const std::string g_strInsertModelSampleTimeConSQL = 
		"insert into tb_eids_model_sample_time_con(id, sample_time_id, monit_point_id, \
        upper_limit_cond, upper_limit_value, lower_limit_cond, lower_limit_value) value(\
        '%1', '%2',	 '%3', '%4',	%5, '%6', %7)" ;

//删除诊断模型样本时间段
const std::string g_strDeleteSampleTimeSQL = 
		"delete from tb_eids_model_sample_time where id = '%s'";

//删除诊断模型样本时间手工筛选条件
const std::string g_strDeleteSampleTimeConSQL = 
		"delete from tb_eids_model_sample_time_con where sample_time_id = '%s'";

//更新诊断模型样本时间段状态
const std::string g_strUpdateModelSampleTimeStateSQL = 
		"update tb_eids_model_sample_time t set t.state = %d, t.samples_sum = 0 where t.id='%s' ";

//更新诊断模型样本时间段状态
const std::string g_strUpdateModelSampleTimeState0SQL = 
		"update tb_eids_model_sample_time t set t.state = '0' where t.model_id='%s' and t.state = '2'";

//删除诊断模型样本时间段状态
const std::string g_strDeleteSampleTimeState2SQL =
		"delete from tb_eids_model_sample_time where state = '2' and model_id='%s'";

//删除诊断模型样本时间段状态"新插入"的手工筛选条件
const std::string g_strDeleteSampleTimeConState2SQL =
		"delete from tb_eids_model_sample_time_con where sample_time_id in \
		(select id from tb_eids_model_sample_time where state = '2' and model_id='%s')";


////////////////////////////////////// SQL Server //////////////////////////////////
//检测数据库连接
const std::string g_strIsConnectSvr2SQL = "select 1";

//获取关系数据库当前时间
const std::string g_strRdbSysDateSvr2SQL = 
		"select Convert(varchar(36),getDate(),120) ";

//获取数据库唯一key
const std::string g_strSysGuidSvr2SQL = 
		"select cast(newid() as varchar(100))";

//查询模型状态与时间段
const std::string g_strModelSampleTimeSvr2SQL = 
		"select model_id, id,		\
		Convert(varchar(36), start_time, 120) start_time,   \
		Convert(varchar(36), end_time, 120) end_time,		\
		step from %stb_eids_model_sample_time		  \
		where state = 1 or state = 4";		

//查询模型状态与时间段(按机组分步式部署)
const std::string g_strModelSampleTimeDistributedSvr2SQL = 
		"select s1.model_id, s1.id,		\
		Convert(varchar(36), s1.start_time, 120) start_time,   \
		Convert(varchar(36), s1.end_time, 120) end_time,		\
		s1.step from %stb_eids_model_sample_time s1,%stb_eids_model s2		  \
		where s1.state = 1 or s1.state = 4 \
		and (s1.model_id = s2.id and s2.set_id in (%s))";					 


//查询样本时间段过滤条件(手动筛选)
const std::string g_strSampleTimeConSvr2SQL = 
		"select monit_point_id,	upper_limit_cond, upper_limit_value,\
        lower_limit_cond,lower_limit_value from tb_eids_model_sample_time_con\
		where sample_time_id = '%s'";

//模型监测条件(模式筛选)
const std::string g_strModelConditionSvr2SQL = 
        "select id, name, local_var, CONCAT(out_var,out_var_func), expression from tb_eids_model_condition where model_id = '%s'";

//查询模型测点
const std::string g_strMonitPointSvr2SQL = 
        "select point_code, ATTR1 from tb_pub_point"; 

//诊断模型样本时间段手工筛选条件
const std::string g_strInsertModelSampleTimeConSvr2SQL =
        "insert into tb_eids_model_sample_time_con(id, sample_time_id, monit_point_id, \
		upper_limit_cond, upper_limit_value, lower_limit_cond, lower_limit_value) \
        '%1', '%2',	'%3', '%4',	%5, '%6', %7)" ;

//诊断模型样本时间段
const std::string g_strInsertModelSampleTimeSvr2SQL =
        "insert into tb_eids_model_sample_time(id, start_time, end_time, \
        step, model_id, model_condition_id, samples_sum, state) values('%1','str_to_date('%2','%Y-%m-%d %H:%i:%s'), str_to_date('%3','%Y-%m-%d %H:%i:%s'), '%4', '%5', '%6', '%7', '%8', '9')";

//删除诊断模型样本时间段
const std::string g_strDeleteSampleTimeSvr2SQL =
		"delete from %stb_eids_model_sample_time where id = '%s'";

//删除诊断模型样本时间手工筛选条件
const std::string g_strDeleteSampleTimeConSvr2SQL =
		"delete from %stb_eids_model_sample_time_con where sample_time_id = '%s'";

//更新诊断模型样本时间段状态
const std::string g_strUpdateModelSampleTimeStateSvr2SQL = 
		"update %stb_eids_model_sample_time set state = %d where id ='%s'";

//更新诊断模型样本时间段状态
const std::string g_strUpdateModelSampleTimeState0Svr2SQL = 
		"update %stb_eids_model_sample_time set state = '0' where model_id ='%s' and state = 2";

//删除诊断模型样本时间段状态
const std::string g_strDeleteSampleTimeState2Svr2SQL =
		"delete from %stb_eids_model_sample_time where state = '2' and model_id='%s'";

//删除诊断模型样本时间段状态"新插入"手工筛选条件
const std::string g_strDeleteSampleTimeConState2Svr2SQL =
		"delete from %stb_eids_model_sample_time_con where sample_time_id in \
		(select id from %stb_eids_model_sample_time where state = '2' and model_id='%s')";

//////////////////////////////样本筛选功能 End/////////////////////////////////////////////

///////////////////////////// 数据相关性分析功能 ///////////////////////////////////////////

///////////////////////////////ORACLE///////////////////////////////////////////
//模型测点
const std::string g_strCorrMonitPointSQL = 
		"select e3.point_id, e4.source_id_original \
		from (select e1.point_id, e1.category_id from tb_eids_model_monit_point e1   \
		where is_del = 0 and e1.category_id in (select category_code from tb_eids_model_monit_category	\
		where model_id = '%s')) e3 left join (select id, source_id_original \
		from tb_pub_point) e4 on e4.id = e3.point_id";

//查询模型状态与时间段
const std::string g_strCorrModelSampleTimeSQL = 
		"select id,		\
		to_char(start_time, 'yyyy-mm-dd hh24:mi:ss') start_time,	  \
		to_char(end_time, 'yyyy-mm-dd hh24:mi:ss') end_time,	   \
		step from tb_eids_model_sample_time		  \
		where model_id ='%s' order by start_time";

//更新诊断模型样本时间段状态
const std::string g_strCorrUpdateSampleTimeCorrStateSQL = 
		"update tb_eids_model_sample_time t set t.corr_state = '%s' where t.model_id='%s'";

//数据相关性分析结果表
const std::string g_strCorrInsertCorrAnalysisDataSQL = 
		"insert into tb_eids_model_corr_analysis( \
		id, model_id, order_no, monit_point_id, t_value, t2_value) \
		values(:v_id<char[100], in>,:v_model_id<char[100], in>,	\
		:v_order_no<int, in>, :v_monit_point_id<char[10000], in>, \
		:v_t_value<char[10000], in>, :v_t2_value<char[10000], in>)";

//删除数据相关性分析结果表
const std::string g_strCorrDeleteCorrAnalysisDataSQL =
		"delete from tb_eids_model_corr_analysis where model_id='%s'";


//更新诊断模型配置状态
const std::string g_strCorrUpdateSampleCorrStateSQL = 
		"update tb_eids_model_sample t set t.state = '%s' where t.model_id='%s' and t.state='%s'";

//查询数据相关性分析任务
const std::string g_strModelSampleCorrSQL = 
		"select model_id from tb_eids_model_sample t group by t.model_id \
		having max(t.state)=min(t.state) and (max(t.state)=1 or max(t.state)=6)";
		//having count(*)=sum(decode(t.state,1,1,0)) \
		//or count(*)=sum(decode(t.state,6,1,0))";

//////////////////////////////////////Sql Server //////////////////////////////////////
//模型测点
const std::string g_strCorrMonitPointSvr2SQL = 
		"select e3.point_id, e4.source_id_original \
		from (select e1.point_id, e1.category_id from %stb_eids_model_monit_point e1   \
		where is_del = 0 and e1.category_id in (select category_code from %stb_eids_model_monit_category	\
		where model_id = '%s')) e3 left join (select id, source_id_original \
		from %stb_pub_point) e4 on e4.id = e3.point_id";


//查询模型状态与时间段
const std::string g_strCorrModelSampleTimeSvr2SQL = 
		"select id,		\
		Convert(varchar(36), start_time, 120) start_time,   \
		Convert(varchar(36), end_time, 120) end_time,		\
		step from %stb_eids_model_sample_time		  \
		where model_id = '%s' order by start_time";

//更新诊断模型样本时间段状态
const std::string g_strCorrUpdateSampleTimeCorrStateSvr2SQL = 
		"update %stb_eids_model_sample_time set corr_state = '%s' where model_id='%s'";

//数据相关性分析结果表
const std::string g_strCorrInsertCorrAnalysisDataSvr2SQL = 
		"insert into %stb_eids_model_corr_analysis(id, model_id, \
		order_no, monit_point_id, t_value, t2_value)  \
		values(:v_id<char[100],in>,:v_model_id<char[100],in>,\
		:v_order_no<int,in>,:v_monit_point_id<varchar(max),in>, \
		:v_t_value<varchar(max),in>,:v_t2_value<varchar(max),in>)";
		//"insert into %stb_eids_model_corr_analysis(id, model_id, \
		//order_no, monit_point_id, t_value, t2_value)  \
		//values(:v_id<char[100], in>,:v_model_id<char[36], in> ,\
		//:v_order_no<char[10],in>, :v_monit_point_id<varchar(max)>, \
		//:v_t_value<varchar(max)>, :v_t2_value<varchar(max)>)";


//删除数据相关性分析结果表
const std::string g_strCorrDeleteCorrAnalysisDataSvr2SQL =
		"delete from %stb_eids_model_corr_analysis where model_id='%s'";


//更新诊断模型配置状态
const std::string g_strCorrUpdateSampleCorrStateSvr2SQL = 
		"update %stb_eids_model_sample set state = '%s' where model_id='%s' and state = '%s'";


//查询数据相关性分析任务
const std::string g_strModelSampleCorrSvr2SQL = 
		"select model_id from %stb_eids_model_sample t GROUP BY	t.model_id  \
		HAVING COUNT (*) = SUM(CASE t.state WHEN 1 THEN 1 ELSE 0 END) \
		or COUNT (*) = SUM(CASE t.state WHEN 6 THEN 1 ELSE 0 END)";

///////////////////////////// 数据相关性分析功能 END ///////////////////////////////////////////
#endif
