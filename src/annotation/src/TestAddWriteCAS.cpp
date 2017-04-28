#include <uima/api.hpp>

#include <pcl/point_types.h>
#include <rs/types/all_types.h>
//RS
#include <rs/scene_cas.h>
#include <rs/utils/time.h>

using namespace uima;


class TestAddWriteCAS : public Annotator
{
private:
  float test_param;

public:

  TyErrorId initialize(AnnotatorContext &ctx)
  {
    outInfo("initialize");
    ctx.extractValue("test_param", test_param);
    return UIMA_ERR_NONE;
  }

  TyErrorId destroy()
  {
    outInfo("destroy");
    return UIMA_ERR_NONE;
  }

  TyErrorId process(CAS &tcas, ResultSpecification const &res_spec)
  {
    outInfo("process start");
    rs::StopWatch clock;
    rs::SceneCas cas(tcas);

    //add a new entity to the CAS
    rs::Query query = rs::create<rs::Query>(tcas);
    query.asJson.set("foobar");
    cas.set("QUERY", query);

    //get back the same thing from the CAS
    rs::Query queryOut = rs::create<rs::Query>(tcas);
    if(cas.get("QUERY", queryOut))
    {
      outInfo("Got: " << queryOut.asJson());
    }
    else
    {
      outWarn("QUERY does not exist in CAS");
    }


    //now the same with an Identifiable
    rs::Identifiable ident = rs::create<rs::Identifiable>(tcas);
    ident.id.set("foobar");
    cas.set("IDENT", query);

    //get back the same thing from the CAS
    rs::Identifiable identOut = rs::create<rs::Identifiable>(tcas);
    if(cas.get("IDENT", identOut))
    {
      outInfo("Got: " << identOut.id());
    }
    else
    {
      outWarn("QUERY does not exist in CAS");
    }

    return UIMA_ERR_NONE;
  }
};

// This macro exports an entry point that is used to create the annotator.
MAKE_AE(TestAddWriteCAS)
