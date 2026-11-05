"""Categorize short feedback comments using transparent keyword rules."""
import argparse
import json
import sys

def cluster(feedback,topics):
    if not isinstance(feedback,list) or not isinstance(topics,dict): raise ValueError("feedback must be a list and topics an object")
    if any(not isinstance(x,str) for x in feedback): raise ValueError("feedback items must be strings")
    if any(not isinstance(k,str) or not isinstance(v,list) or any(not isinstance(w,str) or not w for w in v) for k,v in topics.items()):
        raise ValueError("topics must map names to nonempty keyword strings")
    groups={name:[] for name in topics}
    groups["unmatched"]=[]
    for index,item in enumerate(feedback):
        matched=False
        for name,words in topics.items():
            if any(word.casefold() in item.casefold() for word in words):
                groups[name].append(index)
                matched=True
        if not matched: groups["unmatched"].append(index)
    return {"total":len(feedback),"groups":groups,"counts":{k:len(v) for k,v in groups.items()}}

def main(argv=None):
    p=argparse.ArgumentParser(description="Cluster feedback using keyword topics")
    p.add_argument("file")
    args=p.parse_args(argv)
    try:
        with open(args.file,encoding="utf-8") as f: data=json.load(f)
        if not isinstance(data,dict): raise ValueError("input must be an object")
        result=cluster(data.get("feedback"),data.get("topics"))
    except (OSError,ValueError,TypeError) as exc:
        print(str(exc),file=sys.stderr)
        return 2
    print(json.dumps(result,indent=2))
    return 0
if __name__=="__main__": raise SystemExit(main())
